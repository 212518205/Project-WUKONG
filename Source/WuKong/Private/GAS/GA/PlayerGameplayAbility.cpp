// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/PlayerGameplayAbility.h"

#include "Components/BoxComponent.h"

AWuKongCharacter* UPlayerGameplayAbility::GetOwningCharacter() const
{
	return Cast<AWuKongCharacter>(Super::GetOwningCharacter());
}

void UPlayerGameplayAbility::ToggleOwningWeaponCollision(const bool bIsEnable) const
{
	AWuKongCharacter* WuKong = GetOwningCharacter();
	checkf(WuKong, TEXT("GameplayAbility 应该由 AWuKongCharacter触发"));
	if (!WuKong->HasAuthority())return;
	
	if (bIsEnable)
	{
		WuKong->HitActor.Empty();
		WuKong->GetWeaponBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}else
	{
		WuKong->GetWeaponBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
