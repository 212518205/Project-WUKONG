#pragma once

#include "CoreMinimal.h"
#include "AbilityCharacter.h"
#include "AbilitySystemInterface.h"
#include "GAS/ASC/PlayerAbilitySystemComponent.h"
#include "WuKongCharacter.generated.h"

class UWuKongAttributeSet;
class UWukongWidgetComponent;
class UWidgetComponent;
class UBoxComponent;
class UInitialAbilityData;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class WUKONG_API AWuKongCharacter : public AAbilityCharacter
{
	GENERATED_BODY()

public:
	AWuKongCharacter();

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	UBoxComponent* GetWeaponBoxComponent();
	virtual  UPlayerAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UWuKongAttributeSet* GetWuKongAttributeSet() const { return CachedPlayerAS; }

	/***   ...IAttackableInterface Interface Begin...   ***/
	virtual bool DoesActorAttackable() override;
	/***   ...IAttackableInterface Interface End...     ***/
	
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TObjectPtr<UInitialAbilityData> InitialAbilityData;
	
	UPROPERTY()
	TArray<AActor*> HitActor;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UBoxComponent> WeaponBox;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPlayerAbilitySystemComponent> CachedPlayerASC;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UWuKongAttributeSet> CachedPlayerAS;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UWukongWidgetComponent> WidgetComp;
	
protected:
	void InitCharacterInfo();
	
	UFUNCTION()
	void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnWeaponEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor, 
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowDamage(float DamageTaken) const;
};
