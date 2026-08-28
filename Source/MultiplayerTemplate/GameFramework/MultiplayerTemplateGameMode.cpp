// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/GameFramework/MultiplayerTemplateGameMode.h"
#include "MultiplayerTemplate/Character/MultiplayerTemplateCharacter.h"
#include "MultiplayerTemplate/GameFramework/MultiplayerTemplatePlayerController.h"

AMultiplayerTemplateGameMode::AMultiplayerTemplateGameMode()
{
	DefaultPawnClass = AMultiplayerTemplateCharacter::StaticClass();
	PlayerControllerClass = AMultiplayerTemplatePlayerController::StaticClass();
}
