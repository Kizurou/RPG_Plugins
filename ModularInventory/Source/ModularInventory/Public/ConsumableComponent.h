// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableComponent.h"
#include "ConsumableComponent.generated.h"


/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class MODULARINVENTORY_API UConsumableComponent : public UUsableComponent
{
	GENERATED_BODY()

	UConsumableComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
protected:
	virtual void BeginPlay() override;

	//virtual void UseItemCallback(FGameplayTag Channel, const FUseItemMessage& Payload) override;

	virtual void ServerUseItem_Implementation(const FUseItemMessage& Payload) override;
	virtual bool ServerUseItem_Validate(const FUseItemMessage& Payload) override;
};
