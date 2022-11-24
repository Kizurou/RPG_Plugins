// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "InventoryFragment_Consumable.h"
#include "UsableComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class MODULARINVENTORY_API UUsableComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UUsableComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

	virtual void UseItemCallback(FGameplayTag Channel, const FUseItemMessage& Payload);

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void ServerUseItem(const FUseItemMessage& Payload);

	UPROPERTY(EditDefaultsOnly, Category = "Message")
	TSubclassOf<UInventoryFragment_Usable> UsableClass;
};
