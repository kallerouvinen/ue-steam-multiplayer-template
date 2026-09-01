// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/UI/PauseMenu.h"
#include "MultiplayerTemplate/GameFramework/MultiplayerTemplatePlayerController.h"
#include "MultiplayerTemplate/GameFramework/SteamMultiplayerSubsystem.h"
#include "MultiplayerTemplate/UI/MessageDialog.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UPauseMenu::UPauseMenu(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UMessageDialog> MessageDialogClassFinder(TEXT("/Game/UI/WBP_MessageDialog"));
	if (MessageDialogClassFinder.Succeeded())
	{
		MessageDialogClass = MessageDialogClassFinder.Class;
	}
}

void UPauseMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ContinueButton->OnClicked.AddDynamic(this, &ThisClass::OnContinueButtonClicked);
	InviteFriendsButton->OnClicked.AddDynamic(this, &ThisClass::OnInviteFriendsButtonClicked);
	MainMenuButton->OnClicked.AddDynamic(this, &ThisClass::OnMainMenuButtonClicked);
	QuitGameButton->OnClicked.AddDynamic(this, &ThisClass::OnQuitGameButtonClicked);
}

void UPauseMenu::OnContinueButtonClicked()
{
	if (AMultiplayerTemplatePlayerController* PC = Cast<AMultiplayerTemplatePlayerController>(GetOwningPlayer()))
	{
		PC->TogglePauseMenu();
	}
}

void UPauseMenu::OnInviteFriendsButtonClicked()
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USteamMultiplayerSubsystem* Subsystem = GameInstance->GetSubsystem<USteamMultiplayerSubsystem>())
		{
			Subsystem->ShowInviteUI();
		}
	}
}

void UPauseMenu::OnMainMenuButtonClicked()
{
	if (!MessageDialogClass) return;

	UMessageDialog* Dialog = CreateWidget<UMessageDialog>(this, MessageDialogClass);

	Dialog->SetupDialog(
			FText::FromString("Main Menu"),
			FText::FromString("Are you sure you want to return to the main menu?"),
			FMessageDialogButton(FText::FromString("Yes"), [this]() {
				LeaveSession();
				UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
			}),
			FMessageDialogButton(FText::FromString("No")));

	Dialog->AddToViewport();
}

void UPauseMenu::OnQuitGameButtonClicked()
{
	if (!MessageDialogClass) return;

	UMessageDialog* Dialog = CreateWidget<UMessageDialog>(this, MessageDialogClass);

	Dialog->SetupDialog(
			FText::FromString("Quit Game"),
			FText::FromString("Are you sure you want to quit the game?"),
			FMessageDialogButton(FText::FromString("Yes"), [this]() {
				LeaveSession();
				UKismetSystemLibrary::QuitGame(
						GetWorld(),
						GetOwningPlayer(),
						EQuitPreference::Quit,
						false);
			}),
			FMessageDialogButton(FText::FromString("No")));

	Dialog->AddToViewport();
}

void UPauseMenu::LeaveSession()
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USteamMultiplayerSubsystem* Subsystem = GameInstance->GetSubsystem<USteamMultiplayerSubsystem>())
		{
			Subsystem->LeaveSession();
		}
	}
}
