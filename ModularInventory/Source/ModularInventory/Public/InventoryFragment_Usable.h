// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemDefinition.h"
#include "NativeGameplayTags.h"
#include "InventoryFragment_Usable.generated.h"


USTRUCT(BlueprintType)
struct FUseItemMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Inventory|Usable")
	UInventoryFragment_Usable* Usable = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory|Usable")
	APawn* PawnRef = nullptr;
};
/**
 * 
 */
UCLASS()
class MODULARINVENTORY_API UInventoryFragment_Usable : public UInventoryItemFragment
{
	GENERATED_BODY()
	
public:
	UInventoryFragment_Usable();

	virtual void OnInstanceCreated(UInventoryItemInstance* Instance) override;

	UPROPERTY(BlueprintReadOnly, Category = "Message")
	FGameplayTag MessageChannel;

	UPROPERTY(BlueprintReadOnly, Category = "Message")
	FUseItemMessage UseItemData;
};
