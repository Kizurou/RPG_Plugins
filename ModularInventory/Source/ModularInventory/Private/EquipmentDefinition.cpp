// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentDefinition.h"
#include "BaseGameplayAbility.h"

UEquipmentDefinition::UEquipmentDefinition(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
{
	InstanceType = UEquipmentDefinition::StaticClass();
}
