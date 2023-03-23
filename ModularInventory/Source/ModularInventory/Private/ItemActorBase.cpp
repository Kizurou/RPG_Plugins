// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActorBase.h"
#include "InventoryItemInstance.h"

// Sets default values
AItemActorBase::AItemActorBase(const FObjectInitializer& ObjectInitializer)
{
	ItemDefName = GET_MEMBER_NAME_CHECKED(AItemActorBase, ItemDefinition);
}

void AItemActorBase::UpdateMesh()
{
	if (ItemDefinition != NULL)
	{
		if (ItemInstance)
		{
			// If ItemInstance definition doesn't match ItemDefinition it needs to be destroyed and replaced with an appropriate instance
			if (ItemInstance->GetItemDef() != ItemDefinition)
			{
				ItemInstance->ConditionalBeginDestroy();
				ItemInstance = nullptr;
			}
			else
				return;
		}

		ItemInstance = UInventoryItemInstance::CreateItemInstanceFromDefinition(ItemDefinition, this);
	}
	else
	{
		ItemInstance->ConditionalBeginDestroy();
		ItemInstance = nullptr;
	}
}

#if WITH_EDITOR
void AItemActorBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName() == ItemDefName)
	{
		UpdateMesh();
	}
}
#endif
