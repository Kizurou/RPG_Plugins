// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ASF_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEMFRAMEWORK_API UASF_AssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	UASF_AssetManager();

	// Returns the AssetManager singleton object.
	static UASF_AssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
