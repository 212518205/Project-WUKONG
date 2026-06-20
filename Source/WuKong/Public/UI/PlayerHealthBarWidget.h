

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHealthBarWidget.generated.h"

class UProgressBar;
class UCommonTextBlock;
/**
 * 
 */
UCLASS()
class WUKONG_API UPlayerHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> TextBlock_DamageTaken;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* DamageFloatAnimation;
	
};
