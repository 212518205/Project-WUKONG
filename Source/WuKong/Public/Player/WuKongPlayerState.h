// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "WuKongPlayerState.generated.h"

class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class WUKONG_API AWuKongPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	UPROPERTY(BlueprintReadWrite, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> ASC;
	
};
