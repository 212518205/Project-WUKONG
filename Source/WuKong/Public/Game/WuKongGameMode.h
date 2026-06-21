#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WuKongGameMode.generated.h"

UCLASS()
class WUKONG_API AWuKongGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameMode")
	int32 MaxPlayers = 4;
};
