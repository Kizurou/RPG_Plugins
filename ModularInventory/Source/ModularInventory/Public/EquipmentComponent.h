// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "BaseAbilitySet.h"
#include "UsableComponent.h"
#include "EquipmentComponent.generated.h"


class UEquipmentDefinition;
class UEquipmentInstance;
class UAbilitySystemComponent;
struct FEquipmentList;
class UEquipmentComponent;
struct FUseItemMessage;

/** A single piece of applied equipment */
USTRUCT(BlueprintType)
struct FAppliedEquipmentEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

		FAppliedEquipmentEntry()
	{}

	FString GetDebugString() const;

private:
	friend FEquipmentList;
	friend UEquipmentComponent;

	// The equipment class that got equipped
	UPROPERTY()
	TSubclassOf<UEquipmentDefinition> EquipmentDefinition;

	UPROPERTY()
	UEquipmentInstance* Instance = nullptr;

	// Authority-only list of granted handles
	UPROPERTY(NotReplicated)
	FBaseAbilitySet_GrantedHandles GrantedHandles;
};



/** List of applied equipment */
USTRUCT(BlueprintType)
struct FEquipmentList : public FFastArraySerializer
{
	GENERATED_BODY()

	FEquipmentList()
		: OwnerComponent(nullptr)
	{
	}

	FEquipmentList(UActorComponent* InOwnerComponent)
		: OwnerComponent(InOwnerComponent)
	{
	}

public:
	//~FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	//~End of FFastArraySerializer contract

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FAppliedEquipmentEntry, FEquipmentList>(Entries, DeltaParms, *this);
	}

	UEquipmentInstance* AddEntry(TSubclassOf<UEquipmentDefinition> EquipmentDefinition);
	void RemoveEntry(UEquipmentInstance* Instance);

private:
	UBaseAbilitySystemComponent* GetBaseAbilitySystemComponent() const;

	friend UEquipmentComponent;

private:
	// Replicated list of equipment entries
	UPROPERTY()
		TArray<FAppliedEquipmentEntry> Entries;

	UPROPERTY()
		UActorComponent* OwnerComponent;
};

template<>
struct TStructOpsTypeTraits<FEquipmentList> : public TStructOpsTypeTraitsBase2<FEquipmentList>
{
	enum { WithNetDeltaSerializer = true };
};

UCLASS(meta = (BlueprintSpawnableComponent))
class MODULARINVENTORY_API UEquipmentComponent : public UUsableComponent
{
	GENERATED_BODY()

public:
	UEquipmentComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	UEquipmentInstance* EquipItem(TSubclassOf<UEquipmentDefinition> EquipmentDefinition);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void UnequipItem(UEquipmentInstance* ItemInstance);

	//~UObject interface
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	//~End of UObject interface

	//~UActorComponent interface
	//virtual void EndPlay() override;
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	//~End of UActorComponent interface

	/** Returns the first equipped instance of a given type, or nullptr if none are found */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEquipmentInstance* GetFirstInstanceOfType(TSubclassOf<UEquipmentInstance> InstanceType);

	/** Returns all equipped instances of a given type, or an empty array if none are found */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UEquipmentInstance*> GetEquipmentInstancesOfType(TSubclassOf<UEquipmentInstance> InstanceType) const;

	template <typename T>
	T* GetFirstInstanceOfType()
	{
		return (T*)GetFirstInstanceOfType(T::StaticClass());
	}

protected:
	//virtual void UseItemCallback(FGameplayTag Channel, const FUseItemMessage& Payload) override;

	virtual void ServerUseItem_Implementation(const FUseItemMessage& Payload) override;
	virtual bool ServerUseItem_Validate(const FUseItemMessage& Payload) override;


private:
	UPROPERTY(Replicated)
	FEquipmentList EquipmentList;
	
};
