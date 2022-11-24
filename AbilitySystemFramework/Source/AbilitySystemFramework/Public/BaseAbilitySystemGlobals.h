#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AbilitySystemGlobals.h"
#include "BaseAbilitySystemGlobals.generated.h"

class UAbilitySystemComponent;

UCLASS(Config = Game)
class UBaseAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_UCLASS_BODY()

	//~UAbilitySystemGlobals interface
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	//~End of UAbilitySystemGlobals interface
};