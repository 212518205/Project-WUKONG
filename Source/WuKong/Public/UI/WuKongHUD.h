#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WuKongHUD.generated.h"

class UCommonActiveStack;

UCLASS()
class WUKONG_API UWuKongHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	UCommonActiveStack* GetActiveStack() const { return ActiveStack; }

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonActiveStack> ActiveStack;
};
