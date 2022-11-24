// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"
#include "BaseAbilitySystemComponent.h"
#include "EquipmentInstance.h"
#include "EquipmentDefinition.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "BaseAbilitySet.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "InventoryFragment_Equippable.h"

FString FAppliedEquipmentEntry::GetDebugString() const
{
	return FString::Printf(TEXT("%s of %s"), *GetNameSafe(Instance), *GetNameSafe(EquipmentDefinition.Get()));
}

void FEquipmentList::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	for (int32 Index : RemovedIndices)
	{
		const FAppliedEquipmentEntry& Entry = Entries[Index];
		if (Entry.Instance != nullptr)
		{
			Entry.Instance->OnUnequipped();
		}
	}
}

void FEquipmentList::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	for (int32 Index : AddedIndices)
	{
		const FAppliedEquipmentEntry& Entry = Entries[Index];
		if (Entry.Instance != nullptr)
		{
			Entry.Instance->OnEquipped();
		}
	}
}

void FEquipmentList::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{

}

UEquipmentInstance* FEquipmentList::AddEntry(TSubclassOf<UEquipmentDefinition> EquipmentDefinition)
{
	UEquipmentInstance* Result = nullptr;

	check(EquipmentDefinition != nullptr);
	check(OwnerComponent);
	check(OwnerComponent->GetOwner()->HasAuthority());

	const UEquipmentDefinition* EquipmentCDO = GetDefault<UEquipmentDefinition>(EquipmentDefinition);

	TSubclassOf<UEquipmentInstance> InstanceType = EquipmentCDO->InstanceType;
	if (InstanceType == nullptr)
	{
		InstanceType = UEquipmentInstance::StaticClass();
	}

	FAppliedEquipmentEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.EquipmentDefinition = EquipmentDefinition;
	NewEntry.Instance = NewObject<UEquipmentInstance>(OwnerComponent, InstanceType);
	Result = NewEntry.Instance;

	if (UBaseAbilitySystemComponent* ASC = GetBaseAbilitySystemComponent())
	{
		for (TObjectPtr<const UBaseAbilitySet> AbilitySet : EquipmentCDO->AbilitySetsToGrant)
		{
			AbilitySet->GiveToAbilitySystem(ASC, /*inout*/ &NewEntry.GrantedHandles, Result);
		}
	}
	else
	{
		//@TODO: Warning logging?
	}

	Result->SpawnEquipmentActors(EquipmentCDO->ActorsToSpawn);


	MarkItemDirty(NewEntry);

	return Result;
}

void FEquipmentList::RemoveEntry(UEquipmentInstance* Instance)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FAppliedEquipmentEntry& Entry = *EntryIt;
		if (Entry.Instance == Instance)
		{
			if (UBaseAbilitySystemComponent* ASC = GetBaseAbilitySystemComponent())
			{
				Entry.GrantedHandles.TakeFromAbilitySystem(ASC);
			}

			Instance->DestroyEquipmentActors();


			EntryIt.RemoveCurrent();
			MarkArrayDirty();
		}
	}
}

UBaseAbilitySystemComponent* FEquipmentList::GetBaseAbilitySystemComponent() const
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	return Cast<UBaseAbilitySystemComponent>(OwningActor->GetComponentByClass(UAbilitySystemComponent::StaticClass()));
}


//////////////////////////////////////////////////////////////////////
// UEquipmentComponent


UEquipmentComponent::UEquipmentComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, EquipmentList(this)
{
	SetIsReplicatedByDefault(true);
	bWantsInitializeComponent = true;
	
	UsableClass = UInventoryFragment_Equippable::StaticClass();
}

void UEquipmentComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, EquipmentList);
}

UEquipmentInstance* UEquipmentComponent::EquipItem(TSubclassOf<UEquipmentDefinition> EquipmentDefinition)
{
	UEquipmentInstance* Result = nullptr;
	if (EquipmentDefinition != nullptr)
	{
		Result = EquipmentList.AddEntry(EquipmentDefinition);
		if (Result != nullptr)
		{
			Result->OnEquipped();
		}
	}
	return Result;
}

void UEquipmentComponent::UnequipItem(UEquipmentInstance* ItemInstance)
{
	if (ItemInstance != nullptr)
	{
		ItemInstance->OnUnequipped();
		EquipmentList.RemoveEntry(ItemInstance);
	}
}

bool UEquipmentComponent::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (FAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		UEquipmentInstance* Instance = Entry.Instance;

		if (IsValid(Instance))
		{
			WroteSomething |= Channel->ReplicateSubobject(Instance, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}

void UEquipmentComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UEquipmentComponent::UninitializeComponent()
{
	TArray<UEquipmentInstance*> AllEquipmentInstances;

	// gathering all instances before removal to avoid side effects affecting the equipment list iterator	
	for (const FAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		AllEquipmentInstances.Add(Entry.Instance);
	}

	for (UEquipmentInstance* EquipInstance : AllEquipmentInstances)
	{
		UnequipItem(EquipInstance);
	}

	Super::UninitializeComponent();
}

UEquipmentInstance* UEquipmentComponent::GetFirstInstanceOfType(TSubclassOf<UEquipmentInstance> InstanceType)
{
	for (FAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		if (UEquipmentInstance* Instance = Entry.Instance)

		{
			if (Instance->IsA(InstanceType))
			{
				return Instance;
			}
		}
	}

	return nullptr;
}

void UEquipmentComponent::ServerUseItem_Implementation(const FUseItemMessage& Payload)
{
	Super::ServerUseItem_Implementation(Payload);
	if (UInventoryFragment_Equippable* Equippable = Cast<UInventoryFragment_Equippable>(Payload.Usable))
	{
		EquipItem(Equippable->EquipmentDefinition);
	}
}

bool UEquipmentComponent::ServerUseItem_Validate(const FUseItemMessage& Payload)
{
	return true;
}

TArray<UEquipmentInstance*> UEquipmentComponent::GetEquipmentInstancesOfType(TSubclassOf<UEquipmentInstance> InstanceType) const
{
	TArray<UEquipmentInstance*> Results;
	for (const FAppliedEquipmentEntry& Entry : EquipmentList.Entries)
	{
		if (UEquipmentInstance* Instance = Entry.Instance)
		{
			if (Instance->IsA(InstanceType))
			{
				Results.Add(Instance);
			}
		}
	}
	return Results;
}
