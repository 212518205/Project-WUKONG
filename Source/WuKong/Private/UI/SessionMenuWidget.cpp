#include "UI/SessionMenuWidget.h"
#include "UI/CommonActiveStack.h"
#include "Session/WuKongSessionSubsystem.h"
#include "Player/Controller/WuKongPlayerController.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "GAS/WuKongGameplayTag.h"
#include "WuKongDebugHelper.h"

void USessionMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &USessionMenuWidget::OnHostClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &USessionMenuWidget::OnJoinClicked);
	}
	if (ConnectButton)
	{
		ConnectButton->OnClicked.AddDynamic(this, &USessionMenuWidget::OnConnectClicked);
	}
}

void USessionMenuWidget::OnHostClicked()
{
	Debug::Print(TEXT("[SessionMenu] 创建房间"));

	UWuKongSessionSubsystem* SessionSubsystem = GetGameInstance()->GetSubsystem<UWuKongSessionSubsystem>();
	if (!SessionSubsystem) return;

	SessionSubsystem->OnSessionCreated.AddDynamic(this, &USessionMenuWidget::OnSessionCreated);
	SessionSubsystem->CreateSession(4, true);
}

void USessionMenuWidget::OnJoinClicked()
{
	Debug::Print(TEXT("[SessionMenu] 搜索房间"));

	UWuKongSessionSubsystem* SessionSubsystem = GetGameInstance()->GetSubsystem<UWuKongSessionSubsystem>();
	if (!SessionSubsystem) return;

	SessionSubsystem->OnSessionsFound.AddDynamic(this, &USessionMenuWidget::OnSessionsFound);
	SessionSubsystem->FindSessions(10, true);
}

void USessionMenuWidget::OnConnectClicked()
{
	if (!IPAddressInput) return;

	FString IP = IPAddressInput->GetText().ToString();
	if (IP.IsEmpty()) return;

	Debug::Print(FString::Printf(TEXT("[SessionMenu] 直连: %s"), *IP));

	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;

	UWorld* World = GetWorld();
	if (World && World->GetNetMode() != NM_Standalone)
	{
		Debug::Print(TEXT("[SessionMenu] PIE模式已连接，跳过Travel"));
		UWuKongSessionSubsystem* SessionSubsystem = GetGameInstance()->GetSubsystem<UWuKongSessionSubsystem>();
		if (SessionSubsystem)
		{
			SessionSubsystem->OnSessionJoined.AddDynamic(this, &USessionMenuWidget::OnSessionJoined);
			SessionSubsystem->OnSessionJoined.Broadcast(true);
		}
		return;
	}

	PC->ClientTravel(IP, TRAVEL_Absolute);
}

void USessionMenuWidget::OnSessionCreated(bool bSuccessful)
{
	UWuKongSessionSubsystem* SessionSubsystem = GetGameInstance()->GetSubsystem<UWuKongSessionSubsystem>();
	if (SessionSubsystem)
	{
		SessionSubsystem->OnSessionCreated.RemoveDynamic(this, &USessionMenuWidget::OnSessionCreated);
	}

	if (bSuccessful)
	{
		Debug::Print(TEXT("[SessionMenu] 房间创建成功，开始游戏"));

		if (AWuKongPlayerController* PC = GetOwningPlayer<AWuKongPlayerController>())
		{
			if (UCommonActiveStack* Stack = PC->GetActiveStack())
			{
				Stack->ClearWidgets();
			}
		}
	}
}

void USessionMenuWidget::OnSessionJoined(bool bSuccessful)
{
	UWuKongSessionSubsystem* SessionSubsystem = GetGameInstance()->GetSubsystem<UWuKongSessionSubsystem>();
	if (SessionSubsystem)
	{
		SessionSubsystem->OnSessionJoined.RemoveDynamic(this, &USessionMenuWidget::OnSessionJoined);
	}

	if (bSuccessful)
	{
		Debug::Print(TEXT("[SessionMenu] 加入房间成功，开始游戏"));

		if (AWuKongPlayerController* PC = GetOwningPlayer<AWuKongPlayerController>())
		{
			if (UCommonActiveStack* Stack = PC->GetActiveStack())
			{
				Stack->ClearWidgets();
			}
		}
	}
}

void USessionMenuWidget::OnSessionsFound(const TArray<FBlueprintSessionResult>& Results)
{
	UWuKongSessionSubsystem* SessionSubsystem = GetGameInstance()->GetSubsystem<UWuKongSessionSubsystem>();
	if (SessionSubsystem)
	{
		SessionSubsystem->OnSessionsFound.RemoveDynamic(this, &USessionMenuWidget::OnSessionsFound);
	}

	if (Results.Num() > 0)
	{
		Debug::Print(FString::Printf(TEXT("[SessionMenu] 找到 %d 个房间，加入第一个"), Results.Num()));
		SessionSubsystem->OnSessionJoined.AddDynamic(this, &USessionMenuWidget::OnSessionJoined);
		SessionSubsystem->JoinSession(Results[0]);
	}
	else
	{
		Debug::Print(TEXT("[SessionMenu] 没有找到房间"));
		OnSessionSearchComplete(false);
	}
}
