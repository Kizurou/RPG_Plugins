// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleItemActor.h"
#include "InventoryItemInstance.h"
#include "InventoryFragment_WorldDrop.h"

// Sets default values
ASimpleItemActor::ASimpleItemActor()
{
	if (!MeshComponent)
	{
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
		RootComponent = MeshComponent;
	}
}

void ASimpleItemActor::UpdateMesh()
{
	Super::UpdateMesh();
	
	const UInventoryFragment_WorldDrop* WorldDrop = nullptr;

	if (ItemInstance)
	{
		WorldDrop = ItemInstance->FindFragmentByClass<UInventoryFragment_WorldDrop>();
		if (WorldDrop)
		{
			MeshComponent->SetStaticMesh(WorldDrop->StaticMesh);
			// Need to call RegisterComponent() else mesh will not be visible in editor
			MeshComponent->RegisterComponent();
		}
	}
	else
	{
		MeshComponent->SetStaticMesh(nullptr);
		MeshComponent->UnregisterComponent();
	}
	
}

