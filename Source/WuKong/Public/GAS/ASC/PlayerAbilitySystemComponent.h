// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/ASC/WuKongAbilitySystemComponent.h"                                   
#include "PlayerAbilitySystemComponent.generated.h"


class UInitialAbilityData;
class AAbilityCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUKONG_API UPlayerAbilitySystemComponent : public UWuKongAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UPlayerAbilitySystemComponent();
	
	virtual AAbilityCharacter* GetOwningCharacter() const override;
	
	void OnAbilityInputPressed(const FGameplayTag& InputTag);
	void OnAbilityInputReleased(const FGameplayTag& InputTag);


};
