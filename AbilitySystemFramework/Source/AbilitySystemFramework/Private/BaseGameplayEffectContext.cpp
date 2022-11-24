#include "BaseGameplayEffectContext.h"
#include "Components/PrimitiveComponent.h"
#include "BaseAbilitySourceInterface.h"

FBaseGameplayEffectContext* FBaseGameplayEffectContext::ExtractEffectContext(struct FGameplayEffectContextHandle Handle)
{
	FGameplayEffectContext* BaseEffectContext = Handle.Get();
	if ((BaseEffectContext != nullptr) && BaseEffectContext->GetScriptStruct()->IsChildOf(FBaseGameplayEffectContext::StaticStruct()))
	{
		return (FBaseGameplayEffectContext*)BaseEffectContext;
	}

	return nullptr;
}

void FBaseGameplayEffectContext::SetAbilitySource(const IBaseAbilitySourceInterface* InObject, float InSourceLevel)
{
	AbilitySourceObject = MakeWeakObjectPtr(Cast<const UObject>(InObject));
	// @TODO Investigate if levels are a useful feature
	//SourceLevel = InSourceLevel;
}

const IBaseAbilitySourceInterface* FBaseGameplayEffectContext::GetAbilitySource() const
{
	return Cast<IBaseAbilitySourceInterface>(AbilitySourceObject.Get());
}

bool FBaseGameplayEffectContext::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	FGameplayEffectContext::NetSerialize(Ar, Map, bOutSuccess);

	// Not serialized, for post-activation use:
	// CartridgeID

	return true;
}

const UPhysicalMaterial* FBaseGameplayEffectContext::GetPhysicalMaterial() const
{
	if (const FHitResult* HitResultPtr = GetHitResult())
	{
		return HitResultPtr->PhysMaterial.Get();
	}
	return nullptr;
}

