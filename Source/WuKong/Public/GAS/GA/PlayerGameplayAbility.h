// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/GameplayAbilityBase.h"
#include "Player/WuKongCharacter.h"
#include "PlayerGameplayAbility.generated.h"

class AWuKongCharacter;
/**
 * 
 */
UCLASS()
class WUKONG_API UPlayerGameplayAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()
	
public:
	virtual AWuKongCharacter* GetOwningCharacter() const override;
	
protected:
	UFUNCTION(BlueprintCallable)
	void ToggleOwningWeaponCollision(const bool bIsEnable) const;
	
	
	
};
