// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemDefinition.h"
#include "InventoryFragment_Description.generated.h"

/**
 * 
 */
UCLASS()
class MODULARINVENTORY_API UInventoryFragment_Description : public UInventoryItemFragment
{
	GENERATED_BODY()
	
public:
	UInventoryFragment_Description();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
};
