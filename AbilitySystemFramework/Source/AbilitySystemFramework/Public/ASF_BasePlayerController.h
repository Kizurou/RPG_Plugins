// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ASF_BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEMFRAMEWORK_API AASF_BasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused);

};
