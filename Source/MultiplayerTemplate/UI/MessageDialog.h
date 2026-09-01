// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageDialog.generated.h"

class UButton;
class UTextBlock;

USTRUCT()
struct FMessageDialogButton
{
	GENERATED_BODY()

	FText Label;
	TFunction<void()> OnClicked;

	FMessageDialogButton() = default;
	FMessageDialogButton(FText InLabel, TFunction<void()> InOnClicked = {})
			: Label(MoveTemp(InLabel)), OnClicked(MoveTemp(InOnClicked)) {}
};

/**
 *
 */
UCLASS()
class UMessageDialog : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupDialog(FText InTitle, FText InMessage, const FMessageDialogButton& InButton1, const FMessageDialogButton& InButton2 = {});

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Title;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Description;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Button1;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Button1Label;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UButton> Button2;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Button2Label;

private:
	UFUNCTION()
	void OnButton1Clicked();
	UFUNCTION()
	void OnButton2Clicked();

	TFunction<void()> OnButton1;
	TFunction<void()> OnButton2;
};
