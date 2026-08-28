// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/MainMenu/MainMenuPlayerController.h"
#include "MultiplayerTemplate/MainMenu/MainMenuWidget.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FClassFinder<UMainMenuWidget> MainMenuWidgetClassFinder(TEXT("/Game/MainMenu/WBP_MainMenu"));
	if (MainMenuWidgetClassFinder.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidgetClassFinder.Class;
	}
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController()) return;

	SetInputMode(FInputModeUIOnly());

	if (!ensureMsgf(MainMenuWidgetClass, TEXT("MainMenuWidgetClass is nullptr"))) return;

	MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetClass);
	MainMenuWidget->AddToViewport();
}
