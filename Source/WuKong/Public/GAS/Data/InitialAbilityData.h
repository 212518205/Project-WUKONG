// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InitialAbilityData.generated.h"

/**
 * 
 */

class UGameplayAbility;

USTRUCT()
struct FAbilityInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> AbilityClass;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AbilityTag;
	
};

UCLASS()
class WUKONG_API UInitialAbilityData : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	
	
};
