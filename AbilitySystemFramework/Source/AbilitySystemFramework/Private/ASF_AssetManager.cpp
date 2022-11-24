// Fill out your copyright notice in the Description page of Project Settings.


#include "ASF_AssetManager.h"
#include "ASF_GameplayTags.h"

UASF_AssetManager::UASF_AssetManager()
{

}

UASF_AssetManager& UASF_AssetManager::Get()
{
	check(GEngine);

	UASF_AssetManager* ASFAssetManager = Cast<UASF_AssetManager>(GEngine->AssetManager);
	return *ASFAssetManager;
}

void UASF_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	//Load Native Tags
	FASF_GameplayTags::InitializeNativeTags();
}
