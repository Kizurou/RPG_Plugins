#include "BaseAbilitySystemGlobals.h"
#include "BaseGameplayEffectContext.h"

UBaseAbilitySystemGlobals::UBaseAbilitySystemGlobals(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FGameplayEffectContext* UBaseAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FBaseGameplayEffectContext();
}