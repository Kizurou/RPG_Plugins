// Fill out your copyright notice in the Description page of Project Settings.


#include "ASF_GameplayTags.h"
#include "GameplayTagsManager.h"
#include "Engine/EngineTypes.h"


FASF_GameplayTags FASF_GameplayTags::GameplayTags;

void FASF_GameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(GameplayTagsManager);

	GameplayTagsManager.DoneAddingNativeTags();
}

void FASF_GameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	AddTag(InputTag_Interact, "InputTag.Interact", "An example input.");
}

void FASF_GameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}
