// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/MainMenu/JoinGame/JoinGameWidget.h"
#include "MultiplayerTemplate/GameFramework/SteamMultiplayerSubsystem.h"
#include "MultiplayerTemplate/MainMenu/JoinGame/SessionData.h"
// #include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "Components/CircularThrobber.h"
#include "Components/ListView.h"

UJoinGameWidget::UJoinGameWidget(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
{
}

void UJoinGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	JoinButton->OnClicked.AddDynamic(this, &ThisClass::OnJoinButtonClicked);
	RefreshButton->OnClicked.AddDynamic(this, &ThisClass::OnRefreshButtonClicked);
	BackButton->OnClicked.AddDynamic(this, &ThisClass::OnBackButtonClicked);

	SessionList->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnSessionSelectionChanged);
}

void UJoinGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance) return;

	USteamMultiplayerSubsystem* Subsystem = GameInstance->GetSubsystem<USteamMultiplayerSubsystem>();
	if (!Subsystem) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SteamMultiplayerSubsystem found and bound to OnFindSessionsCompleted"), false);

	Subsystem->OnFindSessionsCompleted.AddDynamic(this, &ThisClass::OnFindSessionsCompleted);

	OnRefreshButtonClicked();
}

void UJoinGameWidget::NativeDestruct()
{
	USteamMultiplayerSubsystem* Subsystem = GetGameInstance()->GetSubsystem<USteamMultiplayerSubsystem>();
	if (Subsystem)
	{
		Subsystem->OnFindSessionsCompleted.RemoveAll(this);
	}

	Super::NativeDestruct();
}

void UJoinGameWidget::OnSessionSelectionChanged(UObject* ListItemObject)
{
	// TODO: Remove when not needed
	UE_LOG(LogTemp, Warning, TEXT("OnSessionSelectionChanged"));
	JoinButton->SetIsEnabled(ListItemObject != nullptr);
}

void UJoinGameWidget::OnJoinButtonClicked()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance) return;

	USteamMultiplayerSubsystem* Subsystem = GameInstance->GetSubsystem<USteamMultiplayerSubsystem>();
	if (!Subsystem) return;

	ULocalPlayer* LocalPlayer = GetOwningPlayer()->GetLocalPlayer();
	if (!LocalPlayer) return;

	USessionData* Session = SessionList->GetSelectedItem<USessionData>();
	if (!Session) return;

	FOnlineSessionSearchResult SessionResult = Session->GetSearchResult();
	if (!SessionResult.IsValid()) return;

	Subsystem->JoinSession(LocalPlayer, SessionResult);
}

void UJoinGameWidget::OnRefreshButtonClicked()
{
	Loader->SetVisibility(ESlateVisibility::Visible);
	SessionList->ClearListItems();
	JoinButton->SetIsEnabled(false);
	RefreshButton->SetIsEnabled(false);

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USteamMultiplayerSubsystem* Subsystem = GameInstance->GetSubsystem<USteamMultiplayerSubsystem>())
		{
			Subsystem->FindSessions();
		}
	}
}

void UJoinGameWidget::OnBackButtonClicked()
{
	RemoveFromParent();
}

void UJoinGameWidget::OnFindSessionsCompleted(TArray<USessionData*> SessionData)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("OnFindSessionsCompleted called"));
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsCompleted called"));
	// TODO: Handle failures also and inform the user that the session search failed

	// TODO: Show Message.Results.Num() somewhere in the window

	Loader->SetVisibility(ESlateVisibility::Collapsed);
	// JoinButton->SetIsEnabled(true);
	RefreshButton->SetIsEnabled(true);

	// TArray<USessionData*> Sessions;

	// for (const USessionData* Session : SessionData)
	// {
	// 	if (Session->GetSearchResult().IsValid())
	// 	{
	// // void SetSearchResult(const FOnlineSessionSearchResult& InSearchResult) { SearchResult = InSearchResult; }
	// // FOnlineSessionSearchResult GetSearchResult() const { return SearchResult; }

	// 		USessionData* NewSessionData = NewObject<USessionData>();
	// 		NewSessionData->SetSearchResult(Session);
	// 		Sessions.Add(NewSessionData);
	// 	}
	// }

	SessionList->SetListItems(SessionData);
}
