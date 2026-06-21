#include "UI/CommonActiveStack.h"
#include "CommonActivatableWidget.h"
#include "Components/OverlaySlot.h"
#include "WuKongDebugHelper.h"

UCommonActivatableWidget* UCommonActiveStack::PushWidgetToStack(TSubclassOf<UCommonActivatableWidget> WidgetClass, FGameplayTag WidgetTag)
{
	if (!WidgetClass) return nullptr;

	for (UCommonActivatableWidget* W : WidgetStack)
	{
		if (W) W->SetVisibility(ESlateVisibility::Collapsed);
	}

	UCommonActivatableWidget* NewWidget = CreateWidget<UCommonActivatableWidget>(GetOwningPlayer(), WidgetClass);
	if (NewWidget)
	{
		AddChild(NewWidget);
		if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(NewWidget->Slot))
		{
			OverlaySlot->SetHorizontalAlignment(HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(VAlign_Fill);
		}
		WidgetStack.Add(NewWidget);
		TaggedWidgets.Add(WidgetTag, NewWidget);
		Debug::Print(FString::Printf(TEXT("[Stack] 推送 [%s]"), *WidgetTag.ToString()));
	}
	return NewWidget;
}

void UCommonActiveStack::PopWidget()
{
	if (WidgetStack.Num() == 0) return;

	UCommonActivatableWidget* TopWidget = WidgetStack.Pop();
	if (TopWidget)
	{
		for (auto It = TaggedWidgets.CreateIterator(); It; ++It)
		{
			if (It.Value() == TopWidget)
			{
				TaggedWidgets.Remove(It.Key());
				break;
			}
		}
		TopWidget->RemoveFromParent();
	}

	if (WidgetStack.Num() > 0)
	{
		if (UCommonActivatableWidget* NewTop = WidgetStack.Last())
		{
			NewTop->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UCommonActiveStack::RemoveWidgetByTag(const FGameplayTag WidgetTag)
{
	UCommonActivatableWidget* Widget = GetWidgetByTag(WidgetTag);
	if (!Widget) return;

	const bool bWasTop = WidgetStack.Num() > 0 && WidgetStack.Last() == Widget;
	WidgetStack.Remove(Widget);
	TaggedWidgets.Remove(WidgetTag);
	Widget->RemoveFromParent();

	if (bWasTop && WidgetStack.Num() > 0)
	{
		if (UCommonActivatableWidget* NewTop = WidgetStack.Last())
		{
			NewTop->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UCommonActiveStack::BringWidgetToTopByTag(const FGameplayTag WidgetTag)
{
	UCommonActivatableWidget* Widget = GetWidgetByTag(WidgetTag);
	if (!Widget) return;
	if (WidgetStack.Num() > 0 && WidgetStack.Last() == Widget) return;

	for (UCommonActivatableWidget* W : WidgetStack)
	{
		if (W) W->SetVisibility(ESlateVisibility::Collapsed);
	}

	WidgetStack.Remove(Widget);
	WidgetStack.Add(Widget);
	Widget->SetVisibility(ESlateVisibility::Visible);
}

UCommonActivatableWidget* UCommonActiveStack::GetWidgetByTag(const FGameplayTag WidgetTag) const
{
	if (TObjectPtr<UCommonActivatableWidget> const* Found = TaggedWidgets.Find(WidgetTag))
	{
		return *Found;
	}
	return nullptr;
}

bool UCommonActiveStack::IsWidgetInStack(const FGameplayTag WidgetTag) const
{
	return TaggedWidgets.Contains(WidgetTag);
}

void UCommonActiveStack::ClearWidgets()
{
	for (UCommonActivatableWidget* W : WidgetStack)
	{
		if (W) W->RemoveFromParent();
	}
	WidgetStack.Empty();
	TaggedWidgets.Empty();
}
