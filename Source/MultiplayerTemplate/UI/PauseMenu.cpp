// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/UI/PauseMenu.h"
#include "MultiplayerTemplate/GameFramework/MultiplayerTemplatePlayerController.h"
#include "MultiplayerTemplate/GameFramework/SteamMultiplayerSubsystem.h"
#include "MultiplayerTemplate/UI/ConfirmationDialog.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UPauseMenu::UPauseMenu(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UConfirmationDialog> ConfirmationDialogClassFinder(TEXT("/Game/UI/WBP_ConfirmationDialog"));
	if (ConfirmationDialogClassFinder.Succeeded())
	{
		ConfirmationDialogClass = ConfirmationDialogClassFinder.Class;
	}
}

void UPauseMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ContinueButton->OnClicked.AddDynamic(this, &ThisClass::OnContinueButtonClicked);
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

void UPauseMenu::OnMainMenuButtonClicked()
{
	UConfirmationDialog* Dialog = CreateWidget<UConfirmationDialog>(this, ConfirmationDialogClass);

	Dialog->SetupDialog(
			FText::FromString("Main Menu"),
			FText::FromString("Are you sure you want to return to the main menu?"),
			FText::FromString("Yes"),
			FText::FromString("No"),
			[this]() {
				LeaveSession();
				UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
			});

	Dialog->AddToViewport();
}

void UPauseMenu::OnQuitGameButtonClicked()
{
	UConfirmationDialog* Dialog = CreateWidget<UConfirmationDialog>(this, ConfirmationDialogClass);

	Dialog->SetupDialog(
			FText::FromString("Quit Game"),
			FText::FromString("Are you sure you want to quit the game?"),
			FText::FromString("Yes"),
			FText::FromString("No"),
			[this]() {
				LeaveSession();
				UKismetSystemLibrary::QuitGame(
						GetWorld(),
						GetOwningPlayer(),
						EQuitPreference::Quit,
						false);
			});

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
