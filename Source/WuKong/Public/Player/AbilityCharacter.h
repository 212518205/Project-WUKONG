// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.h"
#include "GAS/ASC/WuKongAbilitySystemComponent.h"
#include "Interface/AttackableInterface.h"
#include "AbilityCharacter.generated.h"

UCLASS()
class WUKONG_API AAbilityCharacter : public ACharacterBase, public IAbilitySystemInterface, public IAttackableInterface
{
	GENERATED_BODY()

public:
	AAbilityCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/***   ...IAbilitySystemInterface Interface Begin...   ***/
	virtual  UWuKongAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/***   ...IAbilitySystemInterface Interface End...     ***/

	/***   ...IAttackableInterface Interface Begin...   ***/
	virtual bool DoesActorAttackable() override;
	/***   ...IAttackableInterface Interface End...     ***/
};
