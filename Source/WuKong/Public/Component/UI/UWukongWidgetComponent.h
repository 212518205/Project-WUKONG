// 

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "UWukongWidgetComponent.generated.h"

class UPlayerHealthBarWidget;
class UWuKongAttributeSet;
class UPlayerAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WUKONG_API UWukongWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget() override;
	void BindCharacterInfoToUI(UPlayerAbilitySystemComponent* PlayerASC);
	void ShowDamage(const float DamageTaken) const;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UPlayerAbilitySystemComponent> CachedPlayerASC;
	
	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UWuKongAttributeSet> CachedWuKongAS;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UPlayerHealthBarWidget> CachedHealthWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "GAS | Attribute")
	float MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, Category = "GAS | Attribute")
	float Health;
	
	UPROPERTY(BlueprintReadOnly, Category = "GAS | Attribute")
	float TakenDamage;
	
};
