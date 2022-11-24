// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableComponent.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"


UConsumableComponent::UConsumableComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UsableClass = UInventoryFragment_Consumable::StaticClass();
}

void UConsumableComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UConsumableComponent::ServerUseItem_Implementation(const FUseItemMessage& Payload)
{
	Super::ServerUseItem_Implementation(Payload);

	if (UInventoryFragment_Consumable* Consumable = Cast<UInventoryFragment_Consumable>(Payload.Usable))
	{
		if (UAbilitySystemComponent* ASC = Payload.PawnRef->FindComponentByClass<UAbilitySystemComponent>())
		{
			FGameplayAbilitySpec AbilitySpec = ASC->BuildAbilitySpecFromClass(Consumable->AbilityClass);
			ASC->GiveAbilityAndActivateOnce(AbilitySpec);
		}
	}
}

bool UConsumableComponent::ServerUseItem_Validate(const FUseItemMessage& Payload)
{
	// Can do validation here, but for the most part unnecessary
	return true;
}
