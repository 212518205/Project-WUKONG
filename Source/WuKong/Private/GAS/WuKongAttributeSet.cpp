// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/WuKongAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "WuKongDebugHelper.h"
#include "FunctionLibrary/WuKongGameFunctionLibrary.h"
#include "GAS/WuKongGameplayTag.h"
#include "Net/UnrealNetwork.h"

void UWuKongAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UWuKongAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWuKongAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWuKongAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWuKongAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWuKongAttributeSet, CriticalChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWuKongAttributeSet, CriticalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWuKongAttributeSet, DamageTaken, COND_None, REPNOTIFY_Always);
}

void UWuKongAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		const float CurrentHealth = FMath::Clamp(GetHealth(), 0.f, GetMaxHealth());
		SetHealth(CurrentHealth);
	}
	if (const float Damage = GetDamageTaken(); Damage != 0.f && Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float CurrentHealth = FMath::Clamp(GetHealth() - Damage, 0.f, GetMaxHealth());
		SetHealth(CurrentHealth);
		if (CurrentHealth <= 0.f)
		{
			UWuKongGameFunctionLibrary::AddTagToActorIfNone(Data.Target.GetAvatarActor(), Player::Status::Dead);
		}
		else
		{
			FGameplayEventData EventData;
			EventData.Instigator = Data.EffectSpec.GetContext().GetInstigator();
			EventData.Target = Data.Target.GetAvatarActor();
			EventData.EventMagnitude = Damage;
			
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
				Data.Target.GetAvatarActor(),
				Shared::Event::TakeHit,
				EventData
			);

			/***   替代 SendGameplayEventToActor(TakeHit)  `BC@` ***/
			// FGameplayCueParameters CueParams;
			// CueParams.Instigator = Data.EffectSpec.GetContext().GetInstigator();
			// CueParams.NormalizedMagnitude = Damage;
			// CueParams.RawMagnitude = Damage;
			//
			// Data.Target.AddGameplayCue(GameplayCue::Shared::TakeHit, CueParams);
		}
		SetDamageTaken(Damage);
	}
}

void UWuKongAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWuKongAttributeSet, MaxHealth, OldMaxHealth);
}

void UWuKongAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWuKongAttributeSet, Health, OldHealth);
}

void UWuKongAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldAttack) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWuKongAttributeSet, Attack, OldAttack);
}

void UWuKongAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWuKongAttributeSet, Armor, OldArmor);
}

void UWuKongAttributeSet::OnRep_CriticalChance(const FGameplayAttributeData& OldCriticalChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWuKongAttributeSet, CriticalChance, OldCriticalChance);
}

void UWuKongAttributeSet::OnRep_CriticalDamage(const FGameplayAttributeData& OldCriticalDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWuKongAttributeSet, CriticalDamage, OldCriticalDamage);
}

void UWuKongAttributeSet::OnRep_DamageTaken(const FGameplayAttributeData& OldDamageTaken) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWuKongAttributeSet, DamageTaken, OldDamageTaken);
}
