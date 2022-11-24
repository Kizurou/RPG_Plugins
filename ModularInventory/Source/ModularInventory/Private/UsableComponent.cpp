// Fill out your copyright notice in the Description page of Project Settings.


#include "UsableComponent.h"
#include "GameFramework/GameplayMessageSubsystem.h"

UUsableComponent::UUsableComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetIsReplicatedByDefault(true);
	UsableClass = UInventoryFragment_Usable::StaticClass();
}

void UUsableComponent::BeginPlay()
{
	Super::BeginPlay();
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FGameplayTag Channel;
	if (UsableClass != NULL)
	{
		Channel = GetDefault<UInventoryFragment_Usable>(UsableClass)->MessageChannel;
	}
	else
	{
		Channel = GetDefault<UInventoryFragment_Usable>()->MessageChannel;
	}
	MessageSubsystem.RegisterListener<FUseItemMessage>(Channel, this, &ThisClass::UseItemCallback);

}

void UUsableComponent::UseItemCallback(FGameplayTag Channel, const FUseItemMessage& Payload)
{
	if (Payload.PawnRef && Payload.PawnRef == GetPawn<APawn>())
	{
		if (GetNetMode() != ENetMode::NM_Client || GetOwnerRole() == ROLE_AutonomousProxy || GetOwnerRole() == ROLE_Authority)
			ServerUseItem(Payload);
	}
}

void UUsableComponent::ServerUseItem_Implementation(const FUseItemMessage& Payload)
{
	UE_LOG(LogTemp, Warning, TEXT("Usable implementation called on object %s"), *GetName());
}

bool UUsableComponent::ServerUseItem_Validate(const FUseItemMessage& Payload)
{
	return true;
}
