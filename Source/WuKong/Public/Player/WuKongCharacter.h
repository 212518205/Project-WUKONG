#pragma once

#include "CoreMinimal.h"
#include "AbilityCharacter.h"
#include "AbilitySystemInterface.h"
#include "GAS/ASC/PlayerAbilitySystemComponent.h"
#include "WuKongCharacter.generated.h"

class UBoxComponent;
class UInitialAbilityData;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class WUKONG_API AWuKongCharacter : public AAbilityCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWuKongCharacter();

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual  UPlayerAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UBoxComponent* GetWeaponBoxComponent();

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TObjectPtr<UInitialAbilityData> InitialAbilityData;
protected:
	void InitCharacterInfo();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UBoxComponent> WeaponBox;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPlayerAbilitySystemComponent> CachedPlayerASC;
	
	UFUNCTION()
	void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnWeaponEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor, 
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
