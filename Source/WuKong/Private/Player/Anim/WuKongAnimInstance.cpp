// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Anim/WuKongAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "WuKongDebugHelper.h"
#include "Player/WuKongCharacter.h"

void UWuKongAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	OwningCharacter = Cast<AWuKongCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		MovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UWuKongAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	if (OwningCharacter && MovementComponent)
	{	
		GroundSpeed = static_cast<float>(OwningCharacter->GetVelocity().Size2D());
		LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
	}
}
