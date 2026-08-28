// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

class UMainMenuWidget;

/**
 *
 */
UCLASS()
class AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainMenuPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;
	TObjectPtr<UMainMenuWidget> MainMenuWidget;
};
