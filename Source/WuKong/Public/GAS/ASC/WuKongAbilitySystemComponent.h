// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WuKongAbilitySystemComponent.generated.h"

class AAbilityCharacter;
class UInitialAbilityData;
/**
 * 
 */
UCLASS()
class WUKONG_API UWuKongAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:	
	virtual AAbilityCharacter* GetOwningCharacter() const;
	void InitializeCharacterAbility(UInitialAbilityData* InitialInfo);
	void GiveAbilityByClass(TSubclassOf<UGameplayAbility> AbilityClass, int32 AbilityLevel, FGameplayTag AbilityTag);
};
