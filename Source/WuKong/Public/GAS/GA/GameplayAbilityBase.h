// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"

class AAbilityCharacter;
/**
 * 
 */
UCLASS()
class WUKONG_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual  AAbilityCharacter* GetOwningCharacter() const;
	
	UFUNCTION(BlueprintCallable, Category = "GAS")
	FGameplayEffectSpecHandle MakeAttackGameEffectSpecHandle(const TSubclassOf<UGameplayEffect> EffectClass,
		const FGameplayTag DamageType, const float BaseDamageMultiplier) const;
	
	UFUNCTION(BlueprintCallable, Category = "GAS")
	static FActiveGameplayEffectHandle ApplyGameEffectSpecHandleToTarget(AActor* TargetActor,
		const FGameplayEffectSpecHandle& EffectSpecHandle);
};
