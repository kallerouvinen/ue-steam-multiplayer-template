// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MultiplayerTemplatePlayerController.generated.h"

// class UInputMappingContext;

UCLASS()
class AMultiplayerTemplatePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	// TArray<UInputMappingContext*> DefaultMappingContexts;
};
