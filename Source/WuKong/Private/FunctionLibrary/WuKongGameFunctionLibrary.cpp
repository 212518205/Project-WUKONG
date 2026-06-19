// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/WuKongGameFunctionLibrary.h"

#include "WuKongDebugHelper.h"
#include "Player/AbilityCharacter.h"

bool UWuKongGameFunctionLibrary::AddTagToActorIfNone(AActor* ToActor, const FGameplayTag& InTag)
{
	if (UWuKongAbilitySystemComponent* TargetASC = TryGetAbilitySystemComponentFromActor(ToActor); TargetASC && !TargetASC->HasMatchingGameplayTag(InTag))
	{
		TargetASC->AddLooseGameplayTag(InTag);
		return true;
	}
	
	return false;
}

bool UWuKongGameFunctionLibrary::TryRemoveTagFromActor(AActor* ToActor, const FGameplayTag& InTag)
{
	if (UWuKongAbilitySystemComponent* TargetASC = TryGetAbilitySystemComponentFromActor(ToActor);
		TargetASC && TargetASC->HasMatchingGameplayTag(InTag))
	{
		TargetASC->RemoveLooseGameplayTag(InTag);
		return true;
	}
	
	return false;
}

bool UWuKongGameFunctionLibrary::CheckProbability(float Chance)
{
	Chance = FMath::Clamp(Chance, 0.f, 1.f);
	return FMath::FRand() < Chance;
}

bool UWuKongGameFunctionLibrary::DoseActorHaveTag(AActor* ToActor, const FGameplayTag& InTag)
{
	if (const UWuKongAbilitySystemComponent* TargetASC = TryGetAbilitySystemComponentFromActor(ToActor))
	{
		//return TargetASC->HasMatchingGameplayTag(InTag);
		if (TargetASC->HasMatchingGameplayTag(InTag))
		{
			Debug::Print(TEXT("有标签"));
			return true;
		}
		else
		{
			Debug::Print(TEXT("无标签"));
		}
	}
	Debug::Print(TEXT("无ASC无标签"));
	return false;
}

UWuKongAbilitySystemComponent* UWuKongGameFunctionLibrary::TryGetAbilitySystemComponentFromActor(AActor* InActor)
{
	if (const AAbilityCharacter* Character = Cast<AAbilityCharacter>(InActor))
	{
		if (UWuKongAbilitySystemComponent* TargetASC = Character->GetAbilitySystemComponent())
		{
			return TargetASC;
		}
	}
	
	return nullptr;
}
