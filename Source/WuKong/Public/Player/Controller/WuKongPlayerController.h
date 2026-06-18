// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "WuKongPlayerController.generated.h"

class UInitialAbilityData;
class UPlayerAbilitySystemComponent;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class WUKONG_API AWuKongPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	UPlayerAbilitySystemComponent* GetAbilitySystemComponent() ; 
	
protected:
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input | Config")
	TObjectPtr<UInputMappingContext> IMC_Gameplay;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input | Config")
	TObjectPtr<UInputMappingContext> IMC_Ability_Skills;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input | Config")
	TObjectPtr<UInputAction> IA_Move;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input | Config")
	TObjectPtr<UInputAction> IA_Look;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPlayerAbilitySystemComponent> CachedPlayerASC;
	
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TObjectPtr<UInitialAbilityData> InitialAbilityData;
	
};
