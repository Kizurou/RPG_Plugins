// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryFragment_Usable.h"
#include "EquipmentDefinition.h"
#include "InventoryFragment_Equippable.generated.h"

/**
 * 
 */
UCLASS()
class MODULARINVENTORY_API UInventoryFragment_Equippable : public UInventoryFragment_Usable
{
	GENERATED_BODY()

public:
	UInventoryFragment_Equippable();

	UPROPERTY(EditAnywhere, Category = Equipment)
	TSubclassOf<UEquipmentDefinition> EquipmentDefinition;
	
};
