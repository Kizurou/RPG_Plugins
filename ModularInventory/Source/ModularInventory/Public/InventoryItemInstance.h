// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItemInstance.generated.h"

class UInventoryItemFragment;
class UInventoryItemDefinition;

UCLASS(BlueprintType)
class MODULARINVENTORY_API UInventoryItemInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UInventoryItemInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UObject interface
	virtual bool IsSupportedForNetworking() const override { return true; }
	//~End of UObject interface

	TSubclassOf<UInventoryItemDefinition> GetItemDef() const
	{
		return ItemDef;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure = false, meta = (DeterminesOutputType = FragmentClass))
	const TArray<UInventoryItemFragment*> GetAllFragmentsOfClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const;

	UFUNCTION(BlueprintCallable, BlueprintPure = false, meta = (DeterminesOutputType = FragmentClass))
	const UInventoryItemFragment* FindFragmentByClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const;

	template <typename ResultClass>
	const ResultClass* FindFragmentByClass() const
	{
		return (ResultClass*)FindFragmentByClass(ResultClass::StaticClass());
	}

	static UInventoryItemInstance* CreateItemInstanceFromDefinition(TSubclassOf<UInventoryItemDefinition> ItemDefClass, UObject* Outer = nullptr);

private:
	void SetItemDef(TSubclassOf<UInventoryItemDefinition> InDef);

	friend struct FInventoryList;

private:
	UPROPERTY(Replicated)
	TSubclassOf<UInventoryItemDefinition> ItemDef;
};
