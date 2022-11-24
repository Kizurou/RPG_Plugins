// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemInstance.h"
#include "InventoryItemDefinition.h"
#include "Net/UnrealNetwork.h"

UInventoryItemInstance::UInventoryItemInstance(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
{

}

void UInventoryItemInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, ItemDef);
}


const TArray<UInventoryItemFragment*> UInventoryItemInstance::GetAllFragmentsOfClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const
{
	if ((ItemDef != nullptr) && (FragmentClass != nullptr))
	{
		return GetDefault<UInventoryItemDefinition>(ItemDef)->GetAllFragmentsOfClass(FragmentClass);
	}


	return TArray<UInventoryItemFragment*>();
}

const UInventoryItemFragment* UInventoryItemInstance::FindFragmentByClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const
{
	if ((ItemDef != nullptr) && (FragmentClass != nullptr))
	{
		return GetDefault<UInventoryItemDefinition>(ItemDef)->FindFragmentByClass(FragmentClass);
	}

	return nullptr;
}

UInventoryItemInstance* UInventoryItemInstance::CreateItemInstanceFromDefinition(TSubclassOf<UInventoryItemDefinition> ItemDefClass, UObject* Outer)
{
	UInventoryItemInstance* Instance;

	auto& ThreadContext = FUObjectThreadContext::Get();
	if (ThreadContext.IsInConstructor > 0)
	{
		Instance = Outer->CreateDefaultSubobject<UInventoryItemInstance>(TEXT("ItemInstance"));
	}
	else
	{
		Instance = NewObject<UInventoryItemInstance>(Outer);
	}
	Instance->SetItemDef(ItemDefClass);		

	const UInventoryItemDefinition* ItemDef = GetDefault<UInventoryItemDefinition>(ItemDefClass);


	for (UInventoryItemFragment* Fragment : ItemDef->Fragments)
	{
		if (Fragment != nullptr)
		{
			Fragment->OnInstanceCreated(Instance);
		}
	}

	return Instance;
}

void UInventoryItemInstance::SetItemDef(TSubclassOf<UInventoryItemDefinition> InDef)
{
	ItemDef = InDef;
}
