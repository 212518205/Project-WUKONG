// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Controller/WuKongPlayerController.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "EnhancedInputSubsystems.h"
#include "WuKongDebugHelper.h"
#include "Component/Input/WuKongInputComponent.h"
#include "Player/WuKongCharacter.h"


void AWuKongPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(IMC_Ability_Skills && IMC_Gameplay);
	if (InputSystem)
	{
		InputSystem->AddMappingContext(IMC_Gameplay, 0);
		InputSystem->AddMappingContext(IMC_Ability_Skills, 50);
		if (UEnhancedInputUserSettings* UserSetting = InputSystem->GetUserSettings())
		{
			UserSetting->RegisterInputMappingContext(IMC_Gameplay);
			UserSetting->RegisterInputMappingContext(IMC_Ability_Skills);
		}
	}
}

UPlayerAbilitySystemComponent* AWuKongPlayerController::GetAbilitySystemComponent() 
{
	if (!CachedPlayerASC)
	{
		if (const AWuKongCharacter* WuKong = GetPawn<AWuKongCharacter>())
		{
			CachedPlayerASC = WuKong->GetAbilitySystemComponent();
		}
	}
	return CachedPlayerASC;
}

void AWuKongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UWuKongInputComponent* WuKongInputComp = CastChecked<UWuKongInputComponent>(InputComponent);
	WuKongInputComp->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	WuKongInputComp->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
	
	WuKongInputComp->BindAbilityInputAction(InitialAbilityData, this, &ThisClass::AbilityInputPressed,
	                                        &AWuKongPlayerController::AbilityInputReleased);

}

// ReSharper disable CppMemberFunctionMayBeConst
void AWuKongPlayerController::Move(const FInputActionValue& Value)
// ReSharper restore CppMemberFunctionMayBeConst
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (APawn* ControllerPawn = GetPawn())
	{
		ControllerPawn->AddMovementInput(ForwardVector, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightVector, InputAxisVector.X);
	}
}

void AWuKongPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	
	AddPitchInput(InputAxisVector.Y);
	AddYawInput(InputAxisVector.X);
}

void AWuKongPlayerController::AbilityInputPressed(FGameplayTag InputTag)
{
	GetAbilitySystemComponent()->OnAbilityInputPressed(InputTag);
}

void AWuKongPlayerController::AbilityInputReleased(FGameplayTag InputTag)
{
}
