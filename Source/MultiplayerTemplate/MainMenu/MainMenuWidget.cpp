// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/MainMenu/MainMenuWidget.h"
#include "MultiplayerTemplate/MainMenu/HostGame/HostGameWidget.h"
#include "MultiplayerTemplate/MainMenu/JoinGame/JoinGameWidget.h"
#include "MultiplayerTemplate/UI/MessageDialog.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UHostGameWidget> HostGameWidgetClassFinder(TEXT("/Game/MainMenu/WBP_HostGame"));
	if (HostGameWidgetClassFinder.Succeeded())
	{
		HostGameWidgetClass = HostGameWidgetClassFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<UJoinGameWidget> JoinGameWidgetClassFinder(TEXT("/Game/MainMenu/WBP_JoinGame"));
	if (JoinGameWidgetClassFinder.Succeeded())
	{
		JoinGameWidgetClass = JoinGameWidgetClassFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<UMessageDialog> MessageDialogClassFinder(TEXT("/Game/UI/WBP_MessageDialog"));
	if (MessageDialogClassFinder.Succeeded())
	{
		MessageDialogClass = MessageDialogClassFinder.Class;
	}
}

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HostGameButton->OnClicked.AddDynamic(this, &ThisClass::OnHostGameButtonClicked);
	JoinGameButton->OnClicked.AddDynamic(this, &ThisClass::OnJoinGameButtonClicked);
	QuitGameButton->OnClicked.AddDynamic(this, &ThisClass::OnQuitGameButtonClicked);
}

void UMainMenuWidget::OnHostGameButtonClicked()
{
	UHostGameWidget* HostGameMenu = CreateWidget<UHostGameWidget>(this, HostGameWidgetClass);
	HostGameMenu->AddToViewport();
}

void UMainMenuWidget::OnJoinGameButtonClicked()
{
	UJoinGameWidget* JoinGameMenu = CreateWidget<UJoinGameWidget>(this, JoinGameWidgetClass);
	JoinGameMenu->AddToViewport();
}

void UMainMenuWidget::OnQuitGameButtonClicked()
{
	if (!MessageDialogClass) return;

	UMessageDialog* Dialog = CreateWidget<UMessageDialog>(this, MessageDialogClass);

	Dialog->SetupDialog(
			FText::FromString("Quit Game"),
			FText::FromString("Are you sure you want to quit the game?"),
			FMessageDialogButton(FText::FromString("Yes"), [this]() {
				UKismetSystemLibrary::QuitGame(
						GetWorld(),
						GetOwningPlayer(),
						EQuitPreference::Quit,
						false);
			}),
			FMessageDialogButton(FText::FromString("No")));

	Dialog->AddToViewport();
}
