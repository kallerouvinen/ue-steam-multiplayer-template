// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MultiplayerTemplatePlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class UPauseMenu;

UCLASS()
class AMultiplayerTemplatePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMultiplayerTemplatePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	void TogglePauseMenu();

private:
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TObjectPtr<UInputMappingContext> MappingContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> TogglePauseMenuAction;

	TSubclassOf<UPauseMenu> PauseMenuClass;
	TObjectPtr<UPauseMenu> PauseMenu;
};
