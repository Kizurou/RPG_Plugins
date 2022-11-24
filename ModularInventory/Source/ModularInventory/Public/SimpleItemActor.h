// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActorBase.h"
#include "SimpleItemActor.generated.h"

/**
 * A simple actor for common items. It has a single mesh that gets pulled from a WorldData Item Fragment.
 */



UCLASS()
class MODULARINVENTORY_API ASimpleItemActor : public AItemActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleItemActor();

protected:
	virtual void UpdateMesh() override;
	
	TObjectPtr<UStaticMeshComponent> MeshComponent;
};
