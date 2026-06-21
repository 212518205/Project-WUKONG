#include "Player/Controller/WuKongPlayerController.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "EnhancedInputSubsystems.h"
#include "WuKongDebugHelper.h"
#include "Component/Input/WuKongInputComponent.h"
#include "Player/WuKongCharacter.h"
#include "Player/WuKongPlayerState.h"
#include "UI/WuKongHUD.h"
#include "UI/CommonActiveStack.h"
#include "Game/WuKongGameMode.h"
#include "UI/DeathWidget.h"
#include "GAS/WuKongGameplayTag.h"
#include "Input/CommonUIActionRouterBase.h"
#include "Input/CommonUIInputTypes.h"

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

	if (IsLocalController() && HUDClass)
	{
		if (UWuKongHUD* HUD = CreateWidget<UWuKongHUD>(this, HUDClass))
		{
			HUD->AddToViewport(0);
			ActiveStack = HUD->GetActiveStack();

			if (ActiveStack && MainMenuClass)
			{
				ActiveStack->PushWidgetToStack(MainMenuClass, UI::Layer::MainMenu);
				Debug::Print(TEXT("[PlayerController] 显示主菜单"));
			}
		}
	}
}

void AWuKongPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, [this]()
	{
		if (const AWuKongPlayerState* PS = GetPlayerState<AWuKongPlayerState>())
		{
			if (UPlayerAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent())
			{
				if (ASC->HasMatchingGameplayTag(Player::Status::Dead))
				{
					ShowDeathScreen();
				}

				ASC->RegisterGameplayTagEvent(Player::Status::Dead, EGameplayTagEventType::NewOrRemoved)
					.AddLambda([this](const FGameplayTag& Tag, const int32 NewCount)
					{
						if (NewCount > 0)
						{
							Debug::Print(TEXT("[PlayerController] 玩家死亡"));
							ShowDeathScreen();
						}
					});
			}
		}
	}, 0.1f, false);
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

void AWuKongPlayerController::RespawnPlayer()
{
	if (HasAuthority())
	{
		if (AGameModeBase* GM = GetWorld()->GetAuthGameMode())
		{
			GM->RestartPlayer(this);
			Debug::Print(TEXT("[PlayerController] 重生玩家"));
		}
	}
	else
	{
		Server_RequestRespawn();
	}
}

void AWuKongPlayerController::ShowDeathScreen()
{
	if (ActiveStack && DeathWidgetClass)
	{
		ActiveStack->PushWidgetToStack(DeathWidgetClass, UI::Layer::Dialog);
	}
}

void AWuKongPlayerController::Server_RequestRespawn_Implementation()
{
	RespawnPlayer();
}

void AWuKongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UWuKongInputComponent* WuKongInputComp = CastChecked<UWuKongInputComponent>(InputComponent);
	WuKongInputComp->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	WuKongInputComp->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
	WuKongInputComp->BindAction(IA_ToggleMouse, ETriggerEvent::Started, this, &ThisClass::ToggleMouseMode);

	WuKongInputComp->BindAbilityInputAction(InitialAbilityData, this, &ThisClass::AbilityInputPressed,
	                                        &AWuKongPlayerController::AbilityInputReleased);
}

void AWuKongPlayerController::Move(const FInputActionValue& Value)
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

void AWuKongPlayerController::ToggleMouseMode(const FInputActionValue& InputActionValue)
{
	if (UCommonUIActionRouterBase* Router = GetLocalPlayer()->GetSubsystem<UCommonUIActionRouterBase>())
	{
		const EMouseCaptureMode CurrentMode = Router->GetActiveMouseCaptureMode(EMouseCaptureMode::NoCapture);
		const EMouseCaptureMode NewCaptureMode = (CurrentMode == EMouseCaptureMode::NoCapture)
			? EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown
			: EMouseCaptureMode::NoCapture;
		const bool bNewHideCursorDuringCapture = (NewCaptureMode != EMouseCaptureMode::NoCapture);

		const FUIInputConfig NewConfig(ECommonInputMode::All, NewCaptureMode, bNewHideCursorDuringCapture);
		Router->SetActiveUIInputConfig(NewConfig, this);
	}
}
