// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/GameplayAbilityBase.h"

#include "WuKongDebugHelper.h"
#include "FunctionLibrary/WuKongGameFunctionLibrary.h"
#include "Player/AbilityCharacter.h"

AAbilityCharacter* UGameplayAbilityBase::GetOwningCharacter() const
{
	return Cast<AAbilityCharacter>(GetAvatarActorFromActorInfo());
}

FGameplayEffectSpecHandle UGameplayAbilityBase::MakeAttackGameEffectSpecHandle(
	const TSubclassOf<UGameplayEffect> EffectClass, const FGameplayTag DamageType, const float BaseDamageMultiplier) const
{
	const UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	
	FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(EffectClass, 1, ContextHandle);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(DamageType, BaseDamageMultiplier);
	
	return EffectSpecHandle;
}

FActiveGameplayEffectHandle UGameplayAbilityBase::ApplyGameEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& EffectSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UWuKongGameFunctionLibrary::TryGetAbilitySystemComponentFromActor(TargetActor);
	
	check(TargetASC && EffectSpecHandle.IsValid())
	
	return TargetASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetASC);
}
