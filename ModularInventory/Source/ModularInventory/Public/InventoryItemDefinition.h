// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItemDefinition.generated.h"

class UInventoryItemInstance;

UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class UInventoryItemFragment : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnInstanceCreated(UInventoryItemInstance* Instance) {}
};



UCLASS(Blueprintable, Const)
class MODULARINVENTORY_API UInventoryItemDefinition : public UObject
{
	GENERATED_BODY()

public:
	UInventoryItemDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	const UInventoryItemFragment* FindFragmentByClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const;

	const TArray<UInventoryItemFragment*> GetAllFragmentsOfClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display, Instanced)
	TArray<TObjectPtr<UInventoryItemFragment>> Fragments;
	
};
