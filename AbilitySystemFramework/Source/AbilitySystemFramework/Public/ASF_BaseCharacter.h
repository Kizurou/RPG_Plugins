// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "BaseAbilitySet.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Character.h"
#include "ASF_BaseCharacter.generated.h"

class UBaseAbilitySystemComponent;
class UInventoryComponent;
class UEquipmentComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterAttributeChangeDelegate, float, NewValue, float, OldValue);

UCLASS()
class ABILITYSYSTEMFRAMEWORK_API AASF_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AASF_BaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	
	/** Returns the ability system component to use for this actor. It may live on another actor, such as a Pawn using the PlayerState's component */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** Move character forward/backward */
	virtual void MoveForward(const float Value);

	/** Move character left/right */
	virtual void MoveRight(const float Value);

	virtual bool CanMove() const;

protected:

	/** Grants Default Abilities to this character */
	virtual void GrantDefaultAbilities();

	/** Binds ability system component to input from EAbilityInputID enum */
	virtual void BindAbilitySystemComponentInput();

	/** Non input abilities that are granted by default */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;

	/** Input bound abilities that are granted by default */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<UBaseAbilitySet> DefaultAbilitySet;

	TObjectPtr<FBaseAbilitySet_GrantedHandles> DefaultAbilitiesGrantedHandles;

	/** Starting attributes of this character */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	TSubclassOf<class UGameplayEffect> CharacterStartingAttributes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	TSubclassOf<class UGameplayEffect> DefaultAttributeRegeneration;
	
	bool bDefaultAbilitiesGranted;

	/** Refreshes ability actor info and grants default abilities */
	virtual void InitializeAbilitySystemComponent();
	
	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle StaminaChangedDelegateHandle;
	FDelegateHandle MaxStaminaChangedDelegateHandle;

	UFUNCTION(BlueprintPure, Category = "Ability System")
	float GetHealth() const;

	UFUNCTION(BlueprintPure, Category = "Ability System")
	float GetMaxHealth() const;

	virtual void HandleHealthChange(const FOnAttributeChangeData& Data);

	virtual void HandleMaxHealthChange(const FOnAttributeChangeData& Data);

	virtual void HandleStaminaChange(const FOnAttributeChangeData& Data);

	virtual void HandleMaxStaminaChange(const FOnAttributeChangeData& Data);

	virtual void BindAttributeDelegates();

	
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBaseAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	class UASF_AttributeSet* PrimaryAttributeSet;

	// @TODO: Add defaults for the below
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	// UInventoryComponent* InventoryComponent;
	//
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	// UEquipmentComponent* EquipmentComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UASF_InputConfig> DefaultInputConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> DefaultInputMapping;
	
public:

	UPROPERTY(BlueprintAssignable)
	FCharacterAttributeChangeDelegate OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FCharacterAttributeChangeDelegate OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FCharacterAttributeChangeDelegate OnStaminaChanged;
	
	UPROPERTY(BlueprintAssignable)
	FCharacterAttributeChangeDelegate OnMaxStaminaChanged;

protected:

	void DoJump();

	bool CanJump() const;
};
