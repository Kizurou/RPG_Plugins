// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemDefinition.h"

UInventoryItemDefinition::UInventoryItemDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

const UInventoryItemFragment* UInventoryItemDefinition::FindFragmentByClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const
{
	if (FragmentClass != nullptr)
	{
		for (UInventoryItemFragment* Fragment : Fragments)
		{
			if (Fragment && Fragment->IsA(FragmentClass))
			{
				return Fragment;
			}
		}
	}

	return nullptr;
}

const TArray<UInventoryItemFragment*> UInventoryItemDefinition::GetAllFragmentsOfClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const
{
	TArray<UInventoryItemFragment*> OutArr;

	if (FragmentClass != nullptr)
	{
		for (UInventoryItemFragment* Fragment : Fragments)
		{
			if (Fragment && Fragment->IsA(FragmentClass))
			{
				OutArr.Add(Fragment);
			}
		}
	}

	return OutArr;
}
