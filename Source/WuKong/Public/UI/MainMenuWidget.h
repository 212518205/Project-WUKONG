#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MainMenuWidget.generated.h"

class USessionMenuWidget;
class UButton;

UCLASS()
class WUKONG_API UMainMenuWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartGameButton;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USessionMenuWidget> SessionClass;

	UFUNCTION()
	void OnStartGameClicked();
};
