// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InitialAbilityData.generated.h"

/**
 * 
 */

class UInputAction;
class UGameplayEffect;
class UGameplayAbility;

USTRUCT()
struct FAbilityInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> AbilityClass;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AbilityTag;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_Ability;
	
};

UCLASS()
class WUKONG_API UInitialAbilityData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, meta = (ForceInlineRow, Categories = "UI.WidgetStack"))
	TArray<FAbilityInfo> InitialAbilities;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> InitialEffect;
	
};
