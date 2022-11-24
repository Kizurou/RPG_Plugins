// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryFragment_Usable.h"
#include "NativeGameplayTags.h"
#include "InventoryItemInstance.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Usable_Message_Base, "Usable.Message.Base");

UInventoryFragment_Usable::UInventoryFragment_Usable()
{
	MessageChannel = TAG_Usable_Message_Base;
}

void UInventoryFragment_Usable::OnInstanceCreated(UInventoryItemInstance* Instance)
{
	if (Instance)
	{
		if (UActorComponent* Component = Cast<UActorComponent>(Instance->GetOuter()))
		{
			UseItemData.PawnRef = Cast<APawn>(Component->GetOwner());
		}
	}

	UseItemData.Usable = this;
}
