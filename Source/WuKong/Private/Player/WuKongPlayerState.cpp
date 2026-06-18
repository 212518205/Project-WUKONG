// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WuKongPlayerState.h"

#include "GAS/WuKongAttributeSet.h"

AWuKongPlayerState::AWuKongPlayerState()
{
	WuKongAS = CreateDefaultSubobject<UWuKongAttributeSet>(TEXT("WukongAttributeSet"));
	WuKongASC = CreateDefaultSubobject<UPlayerAbilitySystemComponent>(TEXT("WuKongASC"));
	WuKongASC->SetIsReplicated(true);
	WuKongASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UPlayerAbilitySystemComponent* AWuKongPlayerState::GetAbilitySystemComponent() const
{
	return WuKongASC;
}

UWuKongAttributeSet* AWuKongPlayerState::GetWuKongAttributeSet() const
{
	return WuKongAS;
}
