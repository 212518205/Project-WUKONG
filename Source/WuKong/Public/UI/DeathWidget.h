#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "DeathWidget.generated.h"

class UButton;

UCLASS()
class WUKONG_API UDeathWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> RespawnButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

	UFUNCTION()
	void OnRespawnClicked();

	UFUNCTION()
	void OnExitClicked();
};
