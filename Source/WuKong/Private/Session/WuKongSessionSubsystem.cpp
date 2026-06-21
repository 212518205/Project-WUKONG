
#include "Session/WuKongSessionSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Online/OnlineSessionNames.h"
#include "FindSessionsCallbackProxy.h"
#include "OnlineSessionSettings.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "WuKongDebugHelper.h"  

void UWuKongSessionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Debug::Print(TEXT("[WuKongSession] 子系统已初始化。"));
}

void UWuKongSessionSubsystem::Deinitialize()
{
	DestroySession();
	Super::Deinitialize();
}

IOnlineSessionPtr UWuKongSessionSubsystem::GetSessionInterface() const
{
	if (const IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld()))
	{
		return Subsystem->GetSessionInterface();
	}
	return nullptr;
}

void UWuKongSessionSubsystem::CreateSession(const int32 MaxPlayers, const bool bIsLAN)
{
	const IOnlineSessionPtr SessionInterface = GetSessionInterface();
	if (!SessionInterface.IsValid())
	{
		Debug::Print(TEXT("[WuKongSession] 创建会话失败：没有可用的在线会话接口。请检查OnlineSubsystem配置。"));
		OnSessionCreated.Broadcast(false);
		return;
	}

	if ([[maybe_unused]] FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession))
	{
		SessionInterface->DestroySession(NAME_GameSession);
	}

	CreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UWuKongSessionSubsystem::OnCreateSessionComplete);
	CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	const TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsLANMatch = bIsLAN;
	SessionSettings->NumPublicConnections = MaxPlayers;
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bUsesPresence = true;
	SessionSettings->bAllowJoinViaPresence = true;
	SessionSettings->bAllowJoinInProgress = true;
	SessionSettings->bIsDedicated = false;
	SessionSettings->bUseLobbiesIfAvailable = true;
	SessionSettings->BuildUniqueId = 1;

	SessionSettings->bAllowInvites = true;

	Debug::Print(FString::Printf(TEXT("[WuKongSession] 正在创建会话：最大玩家数=%d，局域网=%d"), MaxPlayers, bIsLAN));

	const UWorld* World = GetWorld();
	if (!World)
	{
		OnSessionCreated.Broadcast(false);
		return;
	}

	if (const ULocalPlayer* LocalPlayer = World->GetFirstLocalPlayerFromController(); !SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings))
	{
		Debug::Print(TEXT("[WuKongSession] 创建会话失败。"));
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
		OnSessionCreated.Broadcast(false);
	}
}

void UWuKongSessionSubsystem::FindSessions(const int32 MaxSearchResults, const bool bIsLAN)
{
	const IOnlineSessionPtr SessionInterface = GetSessionInterface();
	if (!SessionInterface.IsValid())
	{
		Debug::Print(TEXT("[WuKongSession] 查找会话失败：没有可用的在线会话接口。"));
		OnSessionsFound.Broadcast(TArray<FBlueprintSessionResult>());
		return;
	}

	// Bind the find sessions delegate
	FindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UWuKongSessionSubsystem::OnFindSessionsComplete);
	FindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);

	// Search settings
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = MaxSearchResults;
	SessionSearch->bIsLanQuery = bIsLAN;
	SessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);

	Debug::Print(FString::Printf(TEXT("[WuKongSession] 正在搜索会话：最大结果数=%d，局域网=%d"), MaxSearchResults, bIsLAN));

	const UWorld* World = GetWorld();
	if (!World)
	{
		OnSessionsFound.Broadcast(TArray<FBlueprintSessionResult>());
		return;
	}

	if (const ULocalPlayer* LocalPlayer = World->GetFirstLocalPlayerFromController(); !SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef()))
	{
		Debug::Print(TEXT("[WuKongSession] 搜索请求失败。"));
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);
		OnSessionsFound.Broadcast(TArray<FBlueprintSessionResult>());
	}
}

void UWuKongSessionSubsystem::JoinSession(const FBlueprintSessionResult& SessionResult)
{
	if (GetWorld()->GetNetMode() != NM_Standalone)
	{
		// 已经连上了，不需要 Travel
		OnSessionJoined.Broadcast(true);
		return;
	}
	
	const IOnlineSessionPtr SessionInterface = GetSessionInterface();
	if (!SessionInterface.IsValid())
	{
		Debug::Print(TEXT("[WuKongSession] 加入会话失败：没有可用的在线会话接口。"));
		OnSessionJoined.Broadcast(false);
		return;
	}

	Debug::Print(TEXT("[WuKongSession] 正在加入会话..."));

	// Bind the join session delegate
	JoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UWuKongSessionSubsystem::OnJoinSessionComplete);
	JoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

	const UWorld* World = GetWorld();
	if (!World)
	{
		OnSessionJoined.Broadcast(false);
		return;
	}

	if (const ULocalPlayer* LocalPlayer = World->GetFirstLocalPlayerFromController(); !SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionResult.OnlineResult))
	{
		Debug::Print(TEXT("[WuKongSession] 加入会话失败。"));
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
		OnSessionJoined.Broadcast(false);
	}
}

void UWuKongSessionSubsystem::DestroySession()
{
	const IOnlineSessionPtr SessionInterface = GetSessionInterface();
	if (!SessionInterface.IsValid())
	{
		return;
	}

	if (const FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession); !ExistingSession)
	{
		return;
	}

	Debug::Print(TEXT("[WuKongSession] 正在销毁会话..."));

	DestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UWuKongSessionSubsystem::OnDestroySessionComplete);
	DestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegate);

	SessionInterface->DestroySession(NAME_GameSession);
}

// --- Private Callbacks ---

void UWuKongSessionSubsystem::OnCreateSessionComplete(FName SessionName, const bool bWasSuccessful)
{
	if (const IOnlineSessionPtr SessionInterface = GetSessionInterface(); SessionInterface.IsValid())
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}

	Debug::Print(FString::Printf(TEXT("[WuKongSession] 创建会话完成：%s"), bWasSuccessful ? TEXT("成功") : TEXT("失败")));

	OnSessionCreated.Broadcast(bWasSuccessful);
}

void UWuKongSessionSubsystem::OnFindSessionsComplete(const bool bWasSuccessful)
{
	if (const IOnlineSessionPtr SessionInterface = GetSessionInterface(); SessionInterface.IsValid())
	{
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);
	}

	TArray<FBlueprintSessionResult> BlueprintResults;

	if (bWasSuccessful && SessionSearch.IsValid())
	{
		for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
		{
			FBlueprintSessionResult BlueprintResult;
			BlueprintResult.OnlineResult = Result;
			BlueprintResults.Add(BlueprintResult);
		}

		Debug::Print(FString::Printf(TEXT("[WuKongSession] 查找会话完成：找到 %d 个会话。"), BlueprintResults.Num()));
	}
	else
	{
		Debug::Print(TEXT("[WuKongSession] 查找会话失败或没有结果。"));
	}

	OnSessionsFound.Broadcast(BlueprintResults);
}

void UWuKongSessionSubsystem::OnJoinSessionComplete(const FName SessionName, const EOnJoinSessionCompleteResult::Type Result)
{
	const IOnlineSessionPtr SessionInterface = GetSessionInterface();
	if (SessionInterface.IsValid())
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
	}

	Debug::Print(FString::Printf(TEXT("[WuKongSession] 加入会话完成：%s"),
		Result == EOnJoinSessionCompleteResult::Success ? TEXT("成功") : TEXT("失败")));

	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		// Get the connection string and travel to the session map
		if (FString ConnectionString; SessionInterface.IsValid() &&
			SessionInterface->GetResolvedConnectString(SessionName, ConnectionString))
		{
			Debug::Print(FString::Printf(TEXT("[WuKongSession] 正在前往：%s"), *ConnectionString));

			if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			{
				PlayerController->ClientTravel(ConnectionString, TRAVEL_Absolute);
			}
		}

		OnSessionJoined.Broadcast(true);
	}
	else
	{
		OnSessionJoined.Broadcast(false);
	}
}

void UWuKongSessionSubsystem::OnDestroySessionComplete(FName SessionName, const bool bWasSuccessful)
{
	if (const IOnlineSessionPtr SessionInterface = GetSessionInterface(); SessionInterface.IsValid())
	{
		SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
	}

	Debug::Print(FString::Printf(TEXT("[WuKongSession] 销毁会话完成：%s"), bWasSuccessful ? TEXT("成功") : TEXT("失败")));

	OnSessionDestroyed.Broadcast(bWasSuccessful);
}