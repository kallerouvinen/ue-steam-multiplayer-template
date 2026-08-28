// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
// class UConfirmationDialog;
class UJoinGameWidget;
class UHostGameWidget;

/**
 *
 */
UCLASS()
class UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> HostGameButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> JoinGameButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> QuitGameButton;

private:
	UFUNCTION()
	void OnHostGameButtonClicked();
	UFUNCTION()
	void OnJoinGameButtonClicked();
	UFUNCTION()
	void OnQuitGameButtonClicked();

	TSubclassOf<UHostGameWidget> HostGameWidgetClass;
	TSubclassOf<UJoinGameWidget> JoinGameWidgetClass;

	// TSubclassOf<UConfirmationDialog> ConfirmationDialogClass;
};
