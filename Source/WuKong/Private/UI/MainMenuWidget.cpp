#include "UI/MainMenuWidget.h"
#include "UI/CommonActiveStack.h"
#include "UI/SessionMenuWidget.h"
#include "Player/Controller/WuKongPlayerController.h"
#include "Components/Button.h"
#include "GAS/WuKongGameplayTag.h"
#include "WuKongDebugHelper.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartGameClicked);
	}
}

void UMainMenuWidget::OnStartGameClicked()
{
	Debug::Print(TEXT("[MainMenu] 开始游戏，打开联机界面"));

	if (const AWuKongPlayerController* PC = GetOwningPlayer<AWuKongPlayerController>())
	{
		if (UCommonActiveStack* Stack = PC->GetActiveStack())
		{
			Stack->PushWidgetToStack(SessionClass, UI::Layer::PauseMenu);
		}
	}
}
