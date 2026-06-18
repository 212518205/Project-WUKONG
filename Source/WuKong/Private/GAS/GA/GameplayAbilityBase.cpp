// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GameplayAbilityBase.h"

#include "Player/AbilityCharacter.h"

AAbilityCharacter* UGameplayAbilityBase::GetOwningCharacter() const
{
	return Cast<AAbilityCharacter>(GetAvatarActorFromActorInfo());
}
