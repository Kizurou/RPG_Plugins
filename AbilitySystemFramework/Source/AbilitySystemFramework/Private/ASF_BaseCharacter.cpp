// Fill out your copyright notice in the Description page of Project Settings.


#include "ASF_BaseCharacter.h"

#include "ASF_AttributeSet.h"
#include "BaseAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ASF_InputComponent.h"

// Sets default values
AASF_BaseCharacter::AASF_BaseCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("Ability System Component"));

	PrimaryAttributeSet = CreateDefaultSubobject<UASF_AttributeSet>(TEXT("Primary Attribute Set"));
}

// Called when the game starts or when spawned
void AASF_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeAbilitySystemComponent();

	BindAttributeDelegates();

	if (GetLocalRole() == ROLE_Authority && ensure(PrimaryAttributeSet))
	{
		// const float CharacterLevel = PrimaryAttributeSet->GetLevel();
		constexpr float CharacterLevel = 1;

		// Give starting attributes to the character;
		if (CharacterStartingAttributes != nullptr)
		{
			const FGameplayEffectContextHandle GameplayEffectContext = AbilitySystemComponent->MakeEffectContext();
			AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(CharacterStartingAttributes, CharacterLevel, GameplayEffectContext);
		}

		if (DefaultAttributeRegeneration != nullptr)
		{
			const FGameplayEffectContextHandle GameplayEffectContext = AbilitySystemComponent->MakeEffectContext();
			AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(DefaultAttributeRegeneration, CharacterLevel, GameplayEffectContext);
		}
	}	
}

// Called to bind functionality to input
void AASF_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AASF_BaseCharacter::DoJump);	

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	if (DefaultInputMapping)
	{
		Subsystem->AddMappingContext(DefaultInputMapping, 0);
	}

	if (DefaultInputConfig)
	{
		if (UASF_InputComponent* ASF_IC = Cast<UASF_InputComponent>(PlayerInputComponent))
		{
			TArray<uint32> BindHandles;
			ASF_IC->BindAbilityActions(DefaultInputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);
		}
	}
}

UAbilitySystemComponent* AASF_BaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AASF_BaseCharacter::MoveForward(const float Value)
{
	if (Value != 0 && CanMove())
	{
		const FRotator Rotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AASF_BaseCharacter::MoveRight(const float Value)
{
	if (Value != 0 && CanMove())
	{
		const FVector Direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

bool AASF_BaseCharacter::CanMove() const
{
	return true;
}

void AASF_BaseCharacter::GrantDefaultAbilities()
{
	if (GetLocalRole() != ROLE_Authority || AbilitySystemComponent == nullptr || bDefaultAbilitiesGranted == true)
	{
		return;
	}

	if(DefaultAbilitySet)
	{
		DefaultAbilitySet->GiveToAbilitySystem(AbilitySystemComponent, DefaultAbilitiesGrantedHandles, this);
	}

	for (TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
	{
		if (Ability != nullptr)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, -1, this));
		}
	}

	bDefaultAbilitiesGranted = true;
}

void AASF_BaseCharacter::BindAbilitySystemComponentInput()
{
}

void AASF_BaseCharacter::InitializeAbilitySystemComponent()
{
	if (ensureAlwaysMsgf(AbilitySystemComponent, TEXT("[%s]: Ability System Component is NULL"), *FString(__FUNCTION__)))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AbilitySystemComponent->RefreshAbilityActorInfo();

		if (GetLocalRole() == ROLE_Authority)
		{
			GrantDefaultAbilities();
		}
	}
}

float AASF_BaseCharacter::GetHealth() const
{
	return PrimaryAttributeSet->GetHealth();
}

float AASF_BaseCharacter::GetMaxHealth() const
{
	return PrimaryAttributeSet->GetMaxHealth();
}

void AASF_BaseCharacter::HandleHealthChange(const FOnAttributeChangeData& Data)
{
	OnHealthChanged.Broadcast(Data.NewValue, Data.OldValue);
}

void AASF_BaseCharacter::HandleMaxHealthChange(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChanged.Broadcast(Data.NewValue, Data.OldValue);
}

void AASF_BaseCharacter::HandleStaminaChange(const FOnAttributeChangeData& Data)
{
	OnStaminaChanged.Broadcast(Data.NewValue, Data.OldValue);
}

void AASF_BaseCharacter::HandleMaxStaminaChange(const FOnAttributeChangeData& Data)
{
	OnMaxStaminaChanged.Broadcast(Data.NewValue, Data.OldValue);
}

void AASF_BaseCharacter::BindAttributeDelegates()
{
	check(AbilitySystemComponent);
	check(PrimaryAttributeSet);

	HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PrimaryAttributeSet->GetHealthAttribute()).AddUObject(this, &AASF_BaseCharacter::HandleHealthChange);
	MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PrimaryAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &AASF_BaseCharacter::HandleMaxHealthChange);
	StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PrimaryAttributeSet->GetStaminaAttribute()).AddUObject(this, &AASF_BaseCharacter::HandleStaminaChange);
	MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PrimaryAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &AASF_BaseCharacter::HandleMaxStaminaChange);
}

void AASF_BaseCharacter::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityInputTagPressed(InputTag);
	}
}

void AASF_BaseCharacter::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityInputTagReleased(InputTag);
	}
}

void AASF_BaseCharacter::DoJump()
{
	if (CanJump())
	{
		Jump();
	}
}

bool AASF_BaseCharacter::CanJump() const
{
	return true;
}

