// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WuKongCharacter.h"

#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/WuKongPlayerState.h"


AWuKongCharacter::AWuKongCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
	WeaponBox->SetupAttachment(GetRootComponent());
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBox->SetCollisionObjectType(ECC_WorldDynamic);
	WeaponBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
}

void AWuKongCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnWeaponBeginOverlap);
	WeaponBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnWeaponEndOverlap);
}

void AWuKongCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitCharacterInfo();
}

void AWuKongCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	InitCharacterInfo();
}

UPlayerAbilitySystemComponent* AWuKongCharacter::GetAbilitySystemComponent() const
{
	return CachedPlayerASC;
}

UBoxComponent* AWuKongCharacter::GetWeaponBoxComponent() 
{
	return WeaponBox;
}

void AWuKongCharacter::InitCharacterInfo()
{
	AWuKongPlayerState* WKPlayerState = GetPlayerState<AWuKongPlayerState>();
	checkf(WKPlayerState, TEXT("WKPlayerState == nullptr in InitCharacterInfo!"));
	CachedPlayerASC = WKPlayerState->GetAbilitySystemComponent();
	CachedPlayerASC->InitAbilityActorInfo(WKPlayerState, this);
	
	if (HasAuthority())
	{
		CachedPlayerASC->InitializeCharacterAbility(InitialAbilityData);
	}
}

void AWuKongCharacter::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AWuKongCharacter::OnWeaponEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


