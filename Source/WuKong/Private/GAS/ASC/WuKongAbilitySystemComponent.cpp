// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ASC/WuKongAbilitySystemComponent.h"

#include "WuKongDebugHelper.h"
#include "GAS/Data/InitialAbilityData.h"
#include "Player/AbilityCharacter.h"

AAbilityCharacter* UWuKongAbilitySystemComponent::GetOwningCharacter() const
{	
	return Cast<AAbilityCharacter>(GetAvatarActor());
}

void UWuKongAbilitySystemComponent::InitializeCharacterAbility(UInitialAbilityData* InitialInfo)
{
	for (auto& [AbilityClass, AbilityTag, IA_UnUse] : InitialInfo->InitialAbilities)
	{
		if (!AbilityClass)continue;
		GiveAbilityByClass(AbilityClass, 1, AbilityTag);
	}
	
	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialInfo->InitialEffect)
	{
		if (!EffectClass)continue;
		const FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(EffectClass, 1, ContextHandle);
		ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UWuKongAbilitySystemComponent::GiveAbilityByClass(const TSubclassOf<UGameplayAbility> AbilityClass, const int32 AbilityLevel, const FGameplayTag AbilityTag)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, AbilityLevel);
	AbilitySpec.SourceObject = GetAvatarActor();
	if (AbilityTag.IsValid())
	{
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityTag);
	}
	
	GiveAbility(AbilitySpec);
}