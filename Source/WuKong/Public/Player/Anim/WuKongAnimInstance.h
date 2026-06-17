// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceBase.h"
#include "WuKongAnimInstance.generated.h"

class UCharacterMovementComponent;
class AWuKongCharacter;
/**
 * 
 */
UCLASS()
class WUKONG_API UWuKongAnimInstance : public UAnimInstanceBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadWrite, Category = "CharacterInfo")
	TObjectPtr<AWuKongCharacter> OwningCharacter;
	
	UPROPERTY(BlueprintReadWrite, Category = "CharacterInfo")
	TObjectPtr<UCharacterMovementComponent> MovementComponent;
	
	UPROPERTY(BlueprintReadWrite, Category = "CharacterInfo")
	float GroundSpeed = 0.f;
	
	UPROPERTY(BlueprintReadWrite, Category = "CharacterInfo")
	float LocomotionDirection;
	
};
