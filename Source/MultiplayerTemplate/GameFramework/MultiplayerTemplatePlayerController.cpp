// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/GameFramework/MultiplayerTemplatePlayerController.h"
#include "MultiplayerTemplate/UI/PauseMenu.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AMultiplayerTemplatePlayerController::AMultiplayerTemplatePlayerController()
{
	static ConstructorHelpers::FClassFinder<UPauseMenu> PauseMenuClassFinder(TEXT("/Game/UI/WBP_PauseMenu"));
	if (PauseMenuClassFinder.Succeeded())
	{
		PauseMenuClass = PauseMenuClassFinder.Class;
	}

	ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(TEXT("InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (MappingContextFinder.Succeeded())
	{
		MappingContext = MappingContextFinder.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> TogglePauseMenuActionFinder(TEXT("InputAction'/Game/Input/Default/IA_TogglePauseMenu.IA_TogglePauseMenu'"));
	if (TogglePauseMenuActionFinder.Succeeded())
	{
		TogglePauseMenuAction = TogglePauseMenuActionFinder.Object;
	}
}

void AMultiplayerTemplatePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController()) return;

	SetInputMode(FInputModeGameOnly());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (MappingContext)
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void AMultiplayerTemplatePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(TogglePauseMenuAction, ETriggerEvent::Started, this, &ThisClass::TogglePauseMenu);
	}
}

void AMultiplayerTemplatePlayerController::TogglePauseMenu()
{
	const bool bPauseMenuIsVisible = PauseMenu && PauseMenu->IsInViewport();

	if (bPauseMenuIsVisible)
	{
		PauseMenu->RemoveFromParent();
		PauseMenu = nullptr;

		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
		GetPawn()->EnableInput(this);
	}
	else
	{
		PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuClass);
		if (PauseMenu)
		{
			PauseMenu->AddToViewport();

			bShowMouseCursor = true;
			SetInputMode(FInputModeGameAndUI());
			GetPawn()->DisableInput(this);
		}
	}
}
