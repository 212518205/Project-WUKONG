// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WuKongCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


AWuKongCharacter::AWuKongCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
}

void AWuKongCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


