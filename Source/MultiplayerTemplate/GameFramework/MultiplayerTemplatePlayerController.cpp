// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/GameFramework/MultiplayerTemplatePlayerController.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void AMultiplayerTemplatePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMultiplayerTemplatePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			// for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			// {
			// 	Subsystem->AddMappingContext(CurrentContext, 0);
			// }

			// for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
			// {
			// 	Subsystem->AddMappingContext(CurrentContext, 0);
			// }
		}
	}
}
