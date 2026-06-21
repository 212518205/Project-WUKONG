#pragma once

#include "CoreMinimal.h"
#include "Components/Overlay.h"
#include "GameplayTagContainer.h"
#include "CommonActiveStack.generated.h"

class UCommonActivatableWidget;

UCLASS()
class WUKONG_API UCommonActiveStack : public UOverlay
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "CommonActiveStack")
	UCommonActivatableWidget* PushWidgetToStack(TSubclassOf<UCommonActivatableWidget> WidgetClass, FGameplayTag WidgetTag);

	UFUNCTION(BlueprintCallable, Category = "CommonActiveStack")
	void PopWidget();

	UFUNCTION(BlueprintCallable, Category = "CommonActiveStack")
	void RemoveWidgetByTag(FGameplayTag WidgetTag);

	UFUNCTION(BlueprintCallable, Category = "CommonActiveStack")
	void BringWidgetToTopByTag(FGameplayTag WidgetTag);

	UFUNCTION(BlueprintCallable, Category = "CommonActiveStack")
	UCommonActivatableWidget* GetWidgetByTag(FGameplayTag WidgetTag) const;

	UFUNCTION(BlueprintCallable, Category = "CommonActiveStack")
	bool IsWidgetInStack(FGameplayTag WidgetTag) const;

	UFUNCTION(BlueprintCallable, Category = "CommonActiveStack")
	void ClearWidgets();

protected:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidget>> TaggedWidgets;

	UPROPERTY()
	TArray<TObjectPtr<UCommonActivatableWidget>> WidgetStack;
};
