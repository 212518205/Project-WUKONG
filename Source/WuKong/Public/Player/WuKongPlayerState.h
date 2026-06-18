// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GAS/ASC/PlayerAbilitySystemComponent.h"
#include "WuKongPlayerState.generated.h"


class UWuKongAttributeSet;
/**
 * 
 */
UCLASS()
class WUKONG_API AWuKongPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AWuKongPlayerState();
	virtual UPlayerAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UWuKongAttributeSet* GetWuKongAttributeSet() const;
	
protected:
	UPROPERTY(BlueprintReadWrite, Category = "GAS")
	TObjectPtr<UPlayerAbilitySystemComponent> WuKongASC;
	
	UPROPERTY(BlueprintReadWrite, Category = "GAS")
	TObjectPtr<UWuKongAttributeSet> WuKongAS;
	
};
