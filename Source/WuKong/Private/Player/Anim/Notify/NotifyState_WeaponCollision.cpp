// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Anim/Notify/NotifyState_WeaponCollision.h"

#include "WuKongDebugHelper.h"
#include "Components/BoxComponent.h"
#include "Player/WuKongCharacter.h"

void UNotifyState_WeaponCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                               float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	if (!MeshComp)return;
	if (AWuKongCharacter* WuKong = MeshComp->GetOwner<AWuKongCharacter>())
	{
		WuKong->HitActor.Empty();
		WuKong->GetWeaponBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void UNotifyState_WeaponCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (!MeshComp)return;
	if (AWuKongCharacter* WuKong = MeshComp->GetOwner<AWuKongCharacter>())
	{
		WuKong->GetWeaponBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
