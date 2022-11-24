// Fill out your copyright notice in the Description page of Project Settings.


#include "ASF_InputConfig.h"
#include "LogChannels.h"

UASF_InputConfig::UASF_InputConfig(const FObjectInitializer& ObjectInitializer)
{

}

const UInputAction* UASF_InputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound /*= true*/) const
{
	for (const FASF_InputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogBaseAbilitySystem, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}

const UInputAction* UASF_InputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound /*= true*/) const
{
	for (const FASF_InputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogBaseAbilitySystem, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
