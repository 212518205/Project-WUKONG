// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FindSessionsCallbackProxy.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "WuKongSessionSubsystem.generated.h"

/** Broadcast when session search results are available. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionsFound, const TArray<FBlueprintSessionResult>&, Results);

/** Broadcast when a session is successfully created or fails. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionCreated, bool, bSuccessful);

/** Broadcast when joining a session succeeds or fails. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionJoined, bool, bSuccessful);

/** Broadcast when a session is destroyed. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionDestroyed, bool, bSuccessful);

/**
 * Manages online session lifecycle: creating, searching, joining, and destroying sessions.
 * Accessible from anywhere via the GameInstance.
 */
UCLASS()
class WUKONG_API UWuKongSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/**
	 * Creates a new online session.
	 * @param MaxPlayers Maximum number of players allowed in the session.
	 * @param bIsLAN     Whether this is a LAN session (no online subsystem required).
	 */
	UFUNCTION(BlueprintCallable, Category = "Session")
	void CreateSession(int32 MaxPlayers = 4, bool bIsLAN = false);

	/**
	 * Searches for available sessions.
	 * Results are broadcast via OnSessionsFound.
	 * @param MaxSearchResults Maximum number of results to return.
	 * @param bIsLAN           Whether to search for LAN sessions.
	 */
	UFUNCTION(BlueprintCallable, Category = "Session")
	void FindSessions(int32 MaxSearchResults = 10, bool bIsLAN = false);

	/**
	 * Joins the specified session. On success, the client travels to the session's map.
	 * @param SessionResult The session to join (from OnSessionsFound results).
	 */
	UFUNCTION(BlueprintCallable, Category = "Session")
	void JoinSession(const FBlueprintSessionResult& SessionResult);

	/** Destroys the current session. */
	UFUNCTION(BlueprintCallable, Category = "Session")
	void DestroySession();

	/** Returns the session interface from the current online subsystem. */
	IOnlineSessionPtr GetSessionInterface() const;

	// --- Delegates for Blueprint binding ---

	UPROPERTY(BlueprintAssignable, Category = "Session")
	FOnSessionsFound OnSessionsFound;

	UPROPERTY(BlueprintAssignable, Category = "Session")
	FOnSessionCreated OnSessionCreated;

	UPROPERTY(BlueprintAssignable, Category = "Session")
	FOnSessionJoined OnSessionJoined;

	UPROPERTY(BlueprintAssignable, Category = "Session")
	FOnSessionDestroyed OnSessionDestroyed;

protected:
	/** Called when session creation completes (bound to OnlineSubsystem delegate). */
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/** Called when session search completes. */
	void OnFindSessionsComplete(bool bWasSuccessful);

	/** Called when joining a session completes. */
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	/** Called when session destruction completes. */
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

private:
	/** Cached session search result for joining after finding. */
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	/** Delegate handles for cleanup. */
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	FDelegateHandle DestroySessionCompleteDelegateHandle;

	/** 在线回话接口. */
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
};
