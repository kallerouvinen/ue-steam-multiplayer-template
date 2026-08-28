// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/MainMenu/JoinGame/JoinGameWidget.h"
#include "MultiplayerTemplate/GameFramework/MultiplayerTemplateGameInstance.h"
#include "MultiplayerTemplate/MainMenu/JoinGame/SessionData.h"
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

	// UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	// FindSessionsSuccessListenerHandle = MessageSubsystem.RegisterListener(
	// 		PaintersTags::TAG_Message_FindSessionsSuccess,
	// 		this,
	// 		&ThisClass::OnFindSessionsSuccess);
	// FindSessionsFailureListenerHandle = MessageSubsystem.RegisterListener(
	// 		PaintersTags::TAG_Message_FindSessionsFailure,
	// 		this,
	// 		&ThisClass::OnFindSessionsFailure);

	OnRefreshButtonClicked();
}

void UJoinGameWidget::NativeDestruct()
{
	// UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	// MessageSubsystem.UnregisterListener(FindSessionsSuccessListenerHandle);
	// MessageSubsystem.UnregisterListener(FindSessionsFailureListenerHandle);

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
	if (UMultiplayerTemplateGameInstance* GameInstance = GetGameInstance<UMultiplayerTemplateGameInstance>())
	{
		// if (USessionData* Session = SessionList->GetSelectedItem<USessionData>())
		// {
		// 	FBlueprintSessionResult SessionResult = Session->GetSessionResult();
		// 	if (SessionResult.OnlineResult.IsValid())
		// 	{
		// 		GameInstance->JoinSessionEvent(SessionResult);
		// 	}
		// }
	}
}

void UJoinGameWidget::OnRefreshButtonClicked()
{
	Loader->SetVisibility(ESlateVisibility::Visible);
	SessionList->ClearListItems();
	JoinButton->SetIsEnabled(false);
	RefreshButton->SetIsEnabled(false);

	// if (UMultiplayerTemplateGameInstance* GameInstance = GetGameInstance<UMultiplayerTemplateGameInstance>())
	// {
	// 	GameInstance->FindSessions();
	// }
}

void UJoinGameWidget::OnBackButtonClicked()
{
	RemoveFromParent();
}

// void UJoinGameWidget::OnFindSessionsSuccess(FGameplayTag Channel, const FFindSessionsSuccessMessage& Message)
// {
// 	// TODO: Show Message.Results.Num() somewhere in the window

// 	Loader->SetVisibility(ESlateVisibility::Collapsed);
// 	// JoinButton->SetIsEnabled(true);
// 	RefreshButton->SetIsEnabled(true);

// 	TArray<USessionData*> Sessions;

// 	for (const FBlueprintSessionResult& Session : Message.Results)
// 	{
// 		if (Session.OnlineResult.IsValid())
// 		{
// 			USessionData* SessionData = NewObject<USessionData>();
// 			SessionData->SetSessionResult(Session);
// 			Sessions.Add(SessionData);
// 		}
// 	}

// 	SessionList->SetListItems(Sessions);
// }

// void UJoinGameWidget::OnFindSessionsFailure(FGameplayTag Channel, const FGenericMessage& Message)
// {
// 	// TODO: Inform the user that the session search failed

// 	Loader->SetVisibility(ESlateVisibility::Collapsed);
// 	RefreshButton->SetIsEnabled(true);
// }
