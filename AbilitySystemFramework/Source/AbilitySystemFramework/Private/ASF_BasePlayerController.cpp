// Fill out your copyright notice in the Description page of Project Settings.


#include "ASF_BasePlayerController.h"
#include "BaseAbilitySystemComponent.h"

void AASF_BasePlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (GetPawn())
	{
		if (UBaseAbilitySystemComponent* ASC = Cast<UBaseAbilitySystemComponent>(GetPawn()->GetComponentByClass(UAbilitySystemComponent::StaticClass())))
		{
			ASC->ProcessAbilityInput(DeltaTime, bGamePaused);
		}
	}
	

	Super::PostProcessInput(DeltaTime, bGamePaused);
}
