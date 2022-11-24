// Fill out your copyright notice in the Description page of Project Settings.


#include "ASF_InputComponent.h"

UASF_InputComponent::UASF_InputComponent(const FObjectInitializer& ObjectInitializer)
{

}



void UASF_InputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}
