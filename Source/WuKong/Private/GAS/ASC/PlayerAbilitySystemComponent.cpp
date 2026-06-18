// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ASC/PlayerAbilitySystemComponent.h"

#include "Player/AbilityCharacter.h"
#include "Player/WuKongCharacter.h"


UPlayerAbilitySystemComponent::UPlayerAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

AAbilityCharacter* UPlayerAbilitySystemComponent::GetOwningCharacter() const
{
	return Cast<AWuKongCharacter>(Super::GetOwningCharacter());
}

void UPlayerAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())return;
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))continue;
		if (!AbilitySpec.IsActive())
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UPlayerAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
}






