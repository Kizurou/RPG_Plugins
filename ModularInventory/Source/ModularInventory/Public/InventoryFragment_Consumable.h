// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryFragment_Usable.h"
#include "InventoryFragment_Consumable.generated.h"


class UGameplayAbility;

/**
 * 
 */
UCLASS()
class MODULARINVENTORY_API UInventoryFragment_Consumable : public UInventoryFragment_Usable
{
	GENERATED_BODY()
	
public:
	UInventoryFragment_Consumable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldConsume = false;
};
