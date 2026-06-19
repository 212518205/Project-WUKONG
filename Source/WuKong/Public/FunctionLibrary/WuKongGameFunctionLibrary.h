// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WuKongGameFunctionLibrary.generated.h"

class UWuKongAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WUKONG_API UWuKongGameFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static bool AddTagToActorIfNone(AActor* ToActor, const FGameplayTag& InTag);
	
	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static bool TryRemoveTagFromActor(AActor* ToActor, const FGameplayTag& InTag);
	
	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static bool CheckProbability(float Chance);
	
	static bool DoseActorHaveTag(AActor* ToActor, const FGameplayTag& InTag);
	static UWuKongAbilitySystemComponent* TryGetAbilitySystemComponentFromActor(AActor* InActor);
};
