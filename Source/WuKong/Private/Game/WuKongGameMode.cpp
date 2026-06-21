#include "Game/WuKongGameMode.h"
#include "GameFramework/PlayerController.h"
#include "WuKongDebugHelper.h"

void AWuKongGameMode::BeginPlay()
{
	Super::BeginPlay();
	Debug::Print(FString::Printf(TEXT("[GameMode] 开始运行，当前网络模式：%d"), static_cast<int32>(GetNetMode())));
}

void AWuKongGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	if (GetNumPlayers() >= MaxPlayers)
	{
		ErrorMessage = TEXT("房间已满");
		Debug::Print(TEXT("[GameMode] 房间已满，拒绝连接"));
	}
}

void AWuKongGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		Debug::Print(FString::Printf(TEXT("[GameMode] 玩家加入，当前人数：%d"), GetNumPlayers()));
		RestartPlayer(NewPlayer);
	}
}

void AWuKongGameMode::Logout(AController* Exiting)
{
	Debug::Print(FString::Printf(TEXT("[GameMode] 玩家离开，剩余人数：%d"), GetNumPlayers() - 1));
	Super::Logout(Exiting);
}
