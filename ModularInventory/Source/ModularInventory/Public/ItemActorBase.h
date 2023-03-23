// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActorBase.generated.h"

class UInventoryItemDefinition;
class UInventoryItemInstance;

UCLASS()
class MODULARINVENTORY_API AItemActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActorBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Updates the item data ensuring ItemInstance and ItemDefinition are valid
	virtual void UpdateMesh();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	TObjectPtr<UInventoryItemInstance> ItemInstance;

	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Inventory)
	TSubclassOf<UInventoryItemDefinition> ItemDefinition;

	// Member Name of the ItemDef variable (Used for detecting when the variable is editted via editor)
	FName ItemDefName;
};
