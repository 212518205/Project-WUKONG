// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AbilityCharacter.h"


// Sets default values
AAbilityCharacter::AAbilityCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAbilityCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

UWuKongAbilitySystemComponent* AAbilityCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

bool AAbilityCharacter::DoesActorAttackable() 
{
	return false;
}

void AAbilityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
