// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryFragment_Equippable.h"
#include "NativeGameplayTags.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Usable_Message_Equippable, "Usable.Message.Equippable");

UInventoryFragment_Equippable::UInventoryFragment_Equippable()
{
	MessageChannel = TAG_Usable_Message_Equippable;
}
