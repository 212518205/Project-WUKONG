// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "WuKongDebugHelper.h"
#include "GAS/Data/InitialAbilityData.h"
#include "WuKongInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUKONG_API UWuKongInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallBackFunc>
	void BindAbilityInputAction(UInitialAbilityData* AbilityData, UserObject* ObjectContext,
	                            CallBackFunc CallBackPressed, CallBackFunc CallBackReleased);
};

template <class UserObject, typename CallBackFunc>
void UWuKongInputComponent::BindAbilityInputAction(UInitialAbilityData* AbilityData, UserObject* ObjectContext,
	CallBackFunc CallBackPressed, CallBackFunc CallBackReleased)
{
	check(AbilityData);

	for (auto& [UnUse, InputTag, InputAction]:AbilityData->InitialAbilities)
	{	
		if (CallBackPressed)
		{
			BindAction(InputAction, ETriggerEvent::Started, ObjectContext, CallBackPressed, InputTag);
		}
		if (CallBackReleased)
		{
			BindAction(InputAction, ETriggerEvent::Completed, ObjectContext, CallBackReleased, InputTag);
		}
	}
}
