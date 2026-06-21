#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "SessionMenuWidget.generated.h"

class UButton;
class UEditableTextBox;
struct FBlueprintSessionResult;

UCLASS()
class WUKONG_API USessionMenuWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> HostButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> JoinButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ConnectButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> IPAddressInput;

	UFUNCTION()
	void OnHostClicked();

	UFUNCTION()
	void OnJoinClicked();

	UFUNCTION()
	void OnConnectClicked();

	void OnSessionCreated(bool bSuccessful);
	void OnSessionJoined(bool bSuccessful);
	void OnSessionsFound(const TArray<FBlueprintSessionResult>& Results);

	UFUNCTION(BlueprintImplementableEvent, Category = "Session")
	void OnSessionSearchComplete(bool bFound);
};
