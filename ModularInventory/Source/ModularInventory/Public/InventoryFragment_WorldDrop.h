// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemDefinition.h"
#include "InventoryFragment_WorldDrop.generated.h"

/**
 * 
 */
UCLASS()
class MODULARINVENTORY_API UInventoryFragment_WorldDrop : public UInventoryItemFragment
{
	GENERATED_BODY()

public:
	UInventoryFragment_WorldDrop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh;
	
};
