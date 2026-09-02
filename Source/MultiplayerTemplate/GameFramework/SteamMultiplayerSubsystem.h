// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerTemplate/GameFramework/Enums.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SteamMultiplayerSubsystem.generated.h"

class USessionData;

DECLARE_LOG_CATEGORY_EXTERN(LogSteamMultiplayer, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFindSessionsComp, TArray<USessionData*>, SessionData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSessionError, const FString&, ErrorMessage, bool, bIsCritical);

/**
 * Steam Multiplayer Subsystem
 * Handles Steam multiplayer functionality for the game instance.
 */
UCLASS()
class USteamMultiplayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void HostSession(FString SessionName, ESessionVisibility Visibility);
	void FindSessions();
	bool JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult);
	bool LeaveSession();
	void ShowInviteUI();
	FString GetPlayerName() const;
	FString GetDefaultSessionName() const;

	FOnFindSessionsComp OnFindSessionsCompleted;
	FOnSessionError OnSessionError;

private:
	void CreateSession();
	FOnlineSessionSettings MakeSessionSettings(ESessionVisibility Visibility, int32 MaxPlayers);

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnSessionUserInviteAccepted(const bool bWasSuccessful, const int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& SearchResult);

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	FString DesiredSessionName;
	ESessionVisibility DesiredSessionVisibility = ESessionVisibility::Public;
	bool bCreateSessionAfterDestroy = false;
};
