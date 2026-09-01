// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/MainMenu/JoinGame/JoinGameWidget.h"
#include "MultiplayerTemplate/GameFramework/SessionData.h"
#include "MultiplayerTemplate/GameFramework/SteamMultiplayerSubsystem.h"
#include "MultiplayerTemplate/UI/ConfirmationDialog.h"
#include "Components/Button.h"
#include "Components/CircularThrobber.h"
#include "Components/ListView.h"

UJoinGameWidget::UJoinGameWidget(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UConfirmationDialog> ConfirmationDialogClassFinder(TEXT("/Game/UI/WBP_ConfirmationDialog"));
	if (ConfirmationDialogClassFinder.Succeeded())
	{
		ConfirmationDialogClass = ConfirmationDialogClassFinder.Class;
	}
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

	Subsystem->OnFindSessionsCompleted.AddDynamic(this, &ThisClass::OnFindSessionsCompleted);
	Subsystem->OnSessionError.AddDynamic(this, &ThisClass::OnSessionError);

	OnRefreshButtonClicked();
}

void UJoinGameWidget::NativeDestruct()
{
	USteamMultiplayerSubsystem* Subsystem = GetGameInstance()->GetSubsystem<USteamMultiplayerSubsystem>();
	if (Subsystem)
	{
		Subsystem->OnFindSessionsCompleted.RemoveAll(this);
		Subsystem->OnSessionError.RemoveAll(this);
	}

	Super::NativeDestruct();
}

void UJoinGameWidget::OnSessionSelectionChanged(UObject* ListItemObject)
{
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
	// TODO: Show Message.Results.Num() somewhere in the window
	// TODO: Select one of the results?

	Loader->SetVisibility(ESlateVisibility::Collapsed);
	// JoinButton->SetIsEnabled(true);
	RefreshButton->SetIsEnabled(true);

	SessionList->SetListItems(SessionData);
}

void UJoinGameWidget::OnSessionError(const FString& ErrorMessage, bool bIsCritical)
{
	UConfirmationDialog* Dialog = CreateWidget<UConfirmationDialog>(this, ConfirmationDialogClass);

	Dialog->SetupDialog(
			FText::FromString("Error"),
			FText::FromString(ErrorMessage),
			FText::FromString("OK"),
			FText::FromString("Cancel"));

	Dialog->AddToViewport();
}
