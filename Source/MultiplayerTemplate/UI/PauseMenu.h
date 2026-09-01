// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class UButton;
class UMessageDialog;

/**
 *
 */
UCLASS()
class UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPauseMenu(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ContinueButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> InviteFriendsButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> MainMenuButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> QuitGameButton;

private:
	UFUNCTION()
	void OnContinueButtonClicked();
	UFUNCTION()
	void OnInviteFriendsButtonClicked();
	UFUNCTION()
	void OnMainMenuButtonClicked();
	UFUNCTION()
	void OnQuitGameButtonClicked();

	void LeaveSession();

	TSubclassOf<UMessageDialog> MessageDialogClass;
};
