#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "WuKongPlayerController.generated.h"

class UWuKongHUD;
class UCommonActivatableWidget;
class UCommonActiveStack;
class UInitialAbilityData;
class UPlayerAbilitySystemComponent;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class WUKONG_API AWuKongPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPlayerAbilitySystemComponent* GetAbilitySystemComponent();
	UCommonActiveStack* GetActiveStack() const { return ActiveStack; }

	void RespawnPlayer();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowDeathScreen();

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(Server, Reliable)
	void Server_RequestRespawn();

	void ToggleMouseMode(const FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input | Config")
	TObjectPtr<UInputMappingContext> IMC_Gameplay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input | Config")
	TObjectPtr<UInputMappingContext> IMC_Ability_Skills;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input | Config")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input | Config")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input | Config")
	TObjectPtr<UInputAction> IA_ToggleMouse;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPlayerAbilitySystemComponent> CachedPlayerASC;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TObjectPtr<UInitialAbilityData> InitialAbilityData;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWuKongHUD> HUDClass;

	UPROPERTY()
	TObjectPtr<UCommonActiveStack> ActiveStack;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCommonActivatableWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCommonActivatableWidget> DeathWidgetClass;
};
