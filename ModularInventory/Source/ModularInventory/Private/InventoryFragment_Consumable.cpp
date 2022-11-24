// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryFragment_Consumable.h"
#include "NativeGameplayTags.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Usable_Message_Consumable, "Usable.Message.Consumable");

UInventoryFragment_Consumable::UInventoryFragment_Consumable()
{
	MessageChannel = TAG_Usable_Message_Consumable;
}
