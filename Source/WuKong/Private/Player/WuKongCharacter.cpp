// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WuKongCharacter.h"

#include "Components/BoxComponent.h"
#include "FunctionLibrary/WuKongGameFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WuKongDebugHelper.h"
#include "Component/UI/UWukongWidgetComponent.h"
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
	WeaponBox->SetupAttachment(GetMesh(), FName("weapon_r"));
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBox->SetCollisionObjectType(ECC_WorldDynamic);
	WeaponBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
	
	WidgetComp = CreateDefaultSubobject<UWukongWidgetComponent>(TEXT("WidgetComp"));
	WidgetComp->SetupAttachment(GetMesh());
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
	CachedPlayerAS = WKPlayerState->GetWuKongAttributeSet();
	CachedPlayerASC->InitAbilityActorInfo(WKPlayerState, this);
	
	if (HasAuthority())
	{
		CachedPlayerASC->InitializeCharacterAbility(InitialAbilityData);
	}
	if (const ENetMode NetMode = GetNetMode(); NetMode != NM_DedicatedServer)
	{
		WidgetComp->BindCharacterInfoToUI(CachedPlayerASC);
	}
}

void AWuKongCharacter::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())return;
	if (OtherActor == this)return;
	if (IAttackableInterface* Attackable = Cast<IAttackableInterface>(OtherActor); !Attackable || !Attackable->DoesActorAttackable())return;
	if (HitActor.Contains(OtherActor))return;
	
	
	HitActor.Add(OtherActor);
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

void AWuKongCharacter::ShowDamage(const float DamageTaken) const
{
	WidgetComp->ShowDamage(DamageTaken);
}


