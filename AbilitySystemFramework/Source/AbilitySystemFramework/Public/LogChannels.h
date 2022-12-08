#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"

ABILITYSYSTEMFRAMEWORK_API DECLARE_LOG_CATEGORY_EXTERN(LogBaseAbilitySystem, Log, All);
ABILITYSYSTEMFRAMEWORK_API FString GetClientServerContextString(UObject* ContextObject = nullptr);