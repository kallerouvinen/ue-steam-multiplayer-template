// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmationDialog.generated.h"

class UButton;
class UTextBlock;

/**
 *
 */
UCLASS()
class UConfirmationDialog : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupDialog(FText InTitle, FText InMessage, FText InConfirmText, FText InCancelText, TFunction<void()> InOnConfirm = 0, TFunction<void()> InOnCancel = 0);
	void SetupDialog(FText InTitle, FText InMessage, FText InConfirmText, TFunction<void()> InOnConfirm = 0);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Title;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Description;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> CancelButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ConfirmLabel;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CancelLabel;

private:
	UFUNCTION()
	void OnConfirmButtonClicked();
	UFUNCTION()
	void OnCancelButtonClicked();

	TFunction<void()> OnConfirm;
	TFunction<void()> OnCancel;
};
