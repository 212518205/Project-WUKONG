// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WuKongCharacter.h"

#include "Components/BoxComponent.h"
#include "FunctionLibrary/WuKongGameFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WuKongDebugHelper.h"
#include "GAS/WuKongGameplayTag.h"
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
	WeaponBox->SetupAttachment(GetMesh(), FName("WeaponSocket"));
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
	UWuKongGameFunctionLibrary::AddTagToActorIfNone(this, Player::Ability::Attackable);
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

bool AWuKongCharacter::DoesActorAttackable() 
{
	return UWuKongGameFunctionLibrary::DoseActorHaveTag(this,Player::Ability::Attackable);
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
	if (!HasAuthority())
	{
		FVector BoxLoc = WeaponBox->GetComponentLocation();
		UE_LOG(LogTemp, Warning, TEXT("服务器 Box 位置: %s"), *BoxLoc.ToString());
		return;
	}
	if (OtherActor == this)
	{
		Debug::Print(TEXT("击中自身"));
		return;
	}
	if (IAttackableInterface* Attackable = Cast<IAttackableInterface>(OtherActor); !Attackable || Attackable->DoesActorAttackable())
	{
		Debug::Print(TEXT("无效Actor"));
		return;
	}
	if (HitActor.Contains(OtherActor))
	{
		Debug::Print("已进入");
		return;
	}
	HitActor.Add(OtherActor);
	Debug::Print(TEXT("Hit Target"));
	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = OtherActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		Shared::Event::MeleeHit,
		Data
	);
}

void AWuKongCharacter::OnWeaponEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


