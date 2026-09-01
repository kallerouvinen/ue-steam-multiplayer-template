// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/GameFramework/SteamMultiplayerSubsystem.h"
#include "MultiplayerTemplate/Constants.h"
#include "MultiplayerTemplate/GameFramework/SessionData.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

DEFINE_LOG_CATEGORY(LogSteamMultiplayer);

void USteamMultiplayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = OnlineSubsystem->GetSessionInterface();

		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &ThisClass::OnCreateSessionComplete);
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &ThisClass::OnDestroySessionComplete);
		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &ThisClass::OnFindSessionsComplete);
		SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &ThisClass::OnJoinSessionComplete);
		SessionInterface->OnSessionUserInviteAcceptedDelegates.AddUObject(this, &ThisClass::OnSessionUserInviteAccepted);
	}
}

void USteamMultiplayerSubsystem::HostSession(FString SessionName)
{
	DesiredSessionName = SessionName;

	if (SessionInterface.IsValid())
	{
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);

		if (ExistingSession)
		{
			bCreateSessionAfterDestroy = true;
			SessionInterface->DestroySession(NAME_GameSession);
		}
		else
		{
			CreateSession(DesiredSessionName);
		}
	}
}

void USteamMultiplayerSubsystem::FindSessions()
{
	if (!SessionInterface.IsValid()) return;

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		// SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 1000;
		// SessionSearch->QuerySettings.Set(SEARCH_KEYWORDS, FString(""), EOnlineComparisonOp::Equals);
		// Examples of setting search parameters
		// SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
		// SessionSearch->QuerySettings.Set(SETTING_MAPNAME, FString(), EOnlineComparisonOp::Equals);
		// SessionSearch->QuerySettings.Set(SEARCH_DEDICATED_ONLY, false, EOnlineComparisonOp::Equals);
		// SessionSearch->QuerySettings.Set(SEARCH_EMPTY_SERVERS_ONLY, false, EOnlineComparisonOp::Equals);
		// SessionSearch->QuerySettings.Set(SEARCH_SECURE_SERVERS_ONLY, false, EOnlineComparisonOp::Equals);
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

bool USteamMultiplayerSubsystem::JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult)
{
	if (!SessionInterface.IsValid()) return false;
	if (!LocalPlayer) return false;

	const int32 LocalUserNum = LocalPlayer->GetControllerId();
	FString JoinSessionString = FString::Printf(TEXT("Player ID %d attempting to join session"), LocalUserNum);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, JoinSessionString, false);
	return SessionInterface->JoinSession(LocalUserNum, NAME_GameSession, SearchResult);
}

bool USteamMultiplayerSubsystem::LeaveSession()
{
	bCreateSessionAfterDestroy = false;

	if (!SessionInterface.IsValid()) return false;

	if (FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession))
	{
		return SessionInterface->DestroySession(NAME_GameSession);
	}

	return false;
}

void USteamMultiplayerSubsystem::CreateSession(FString SessionName)
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bAllowJoinInProgress = true;
		SessionSettings.bAllowJoinViaPresence = true;
		// SessionSettings.bIsLANMatch = false;
		SessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
		SessionSettings.NumPrivateConnections = 0;
		SessionSettings.NumPublicConnections = 4;
		SessionSettings.bShouldAdvertise = true;
		// In Steam, bUsesPresence and bUseLobbiesIfAvailable have equivalent meaning and should have the same value
		SessionSettings.bUsesPresence = true;
		SessionSettings.bUseLobbiesIfAvailable = true;

		if (!DesiredSessionName.IsEmpty())
		{
			SessionSettings.Set(
					SESSION_NAME_SETTINGS_KEY,
					DesiredSessionName,
					EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		}

		// TODO: We could also use UserId as the first param
		if (!SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings))
		{
			// OnCreateSessionComplete.Broadcast(false);
		}
	}
}

void USteamMultiplayerSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (!bWasSuccessful) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Session created successfully."), false);

	FString URL = FString::Printf(TEXT("%s?listen"), *GAME_MAP_PATH);
	GetWorld()->ServerTravel(URL, true);
}

void USteamMultiplayerSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		OnSessionError.Broadcast(TEXT("Failed to destroy existing session"), false);
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session: %s"), *SessionName.ToString());
		// Still try to create new session even if destroy failed
	}

	if (bCreateSessionAfterDestroy)
	{
		bCreateSessionAfterDestroy = false;
		CreateSession(DesiredSessionName);
	}
}

void USteamMultiplayerSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("OnFindSessionsComplete called"), false);

	if (!bWasSuccessful)
	{
		OnSessionError.Broadcast(TEXT("Failed to find sessions. Check your connection."), false);
		UE_LOG(LogTemp, Warning, TEXT("Session search failed"));
		OnFindSessionsCompleted.Broadcast(TArray<USessionData*>()); // Broadcast empty array
		return;
	}

	if (!SessionSearch.IsValid())
	{
		OnSessionError.Broadcast(TEXT("Invalid session search"), false);
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Processing found sessions"), false);

	TArray<USessionData*> Sessions;

	for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
	{
		USessionData* SessionData = NewObject<USessionData>();
		SessionData->SetSearchResult(SearchResult);
		Sessions.Add(SessionData);
	}

	UE_LOG(LogTemp, Log, TEXT("Found %d sessions"), Sessions.Num());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Found sessions: " + FString::FromInt(Sessions.Num())), false);
	OnFindSessionsCompleted.Broadcast(Sessions);
}

void USteamMultiplayerSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		FString ErrorMsg;
		switch (Result)
		{
			case EOnJoinSessionCompleteResult::SessionIsFull:
				ErrorMsg = TEXT("Cannot join: Session is full");
				break;
			case EOnJoinSessionCompleteResult::SessionDoesNotExist:
				ErrorMsg = TEXT("Cannot join: Session no longer exists");
				break;
			case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
				ErrorMsg = TEXT("Cannot join: Could not retrieve server address");
				break;
			case EOnJoinSessionCompleteResult::AlreadyInSession:
				ErrorMsg = TEXT("Cannot join: Already in a session");
				break;
			case EOnJoinSessionCompleteResult::UnknownError:
			default:
				ErrorMsg = TEXT("Failed to join session: Unknown error");
				break;
		}
		OnSessionError.Broadcast(ErrorMsg, false);
		UE_LOG(LogTemp, Error, TEXT("Join session failed: %s"), *ErrorMsg);
		return;
	}

	if (!SessionInterface.IsValid())
	{
		OnSessionError.Broadcast(TEXT("Invalid session interface after join"), true);
		return;
	}

	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		const FString ErrorMsg = TEXT("Failed to get server address");
		OnSessionError.Broadcast(ErrorMsg, true);
		UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMsg);
		return;
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (APlayerController* PlayerController = GameInstance->GetFirstLocalPlayerController(GetWorld()))
		{
			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		}
		else
		{
			OnSessionError.Broadcast(TEXT("No player controller found"), true);
		}
	}
	else
	{
		OnSessionError.Broadcast(TEXT("No game instance found"), true);
	}
}

void USteamMultiplayerSubsystem::OnSessionUserInviteAccepted(const bool bWasSuccessful, const int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& SearchResult)
{
	if (!bWasSuccessful) return;

	UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance) return;

	APlayerController* PlayerController = GameInstance->GetFirstLocalPlayerController(GetWorld());
	if (!PlayerController) return;

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer) return;

	JoinSession(LocalPlayer, SearchResult);
}
