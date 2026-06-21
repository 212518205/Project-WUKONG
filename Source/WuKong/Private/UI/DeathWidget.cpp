#include "UI/DeathWidget.h"
#include "UI/CommonActiveStack.h"
#include "UI/MainMenuWidget.h"
#include "Session/WuKongSessionSubsystem.h"
#include "Player/Controller/WuKongPlayerController.h"
#include "Components/Button.h"
#include "GAS/WuKongGameplayTag.h"
#include "WuKongDebugHelper.h"

void UDeathWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RespawnButton)
	{
		RespawnButton->OnClicked.AddDynamic(this, &UDeathWidget::OnRespawnClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UDeathWidget::OnExitClicked);
	}
}

void UDeathWidget::OnRespawnClicked()
{
	Debug::Print(TEXT("[DeathWidget] 重生"));

	if (AWuKongPlayerController* PC = GetOwningPlayer<AWuKongPlayerController>())
	{
		PC->RespawnPlayer();

		if (UCommonActiveStack* Stack = PC->GetActiveStack())
		{
			Stack->PopWidget();
		}
	}
}

void UDeathWidget::OnExitClicked()
{
	Debug::Print(TEXT("[DeathWidget] 退出到主菜单"));

	if (UWuKongSessionSubsystem* SessionSubsystem = GetGameInstance()->GetSubsystem<UWuKongSessionSubsystem>())
	{
		SessionSubsystem->DestroySession();
	}

	if (AWuKongPlayerController* PC = GetOwningPlayer<AWuKongPlayerController>())
	{
		if (UCommonActiveStack* Stack = PC->GetActiveStack())
		{
			Stack->ClearWidgets();
			Stack->PushWidgetToStack(UMainMenuWidget::StaticClass(), UI::Layer::MainMenu);
		}
	}
}
