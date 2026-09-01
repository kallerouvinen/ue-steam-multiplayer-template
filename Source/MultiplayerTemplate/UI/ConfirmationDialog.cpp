// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/UI/ConfirmationDialog.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UConfirmationDialog::SetupDialog(FText InTitle, FText InMessage, FText InConfirmText, FText InCancelText, TFunction<void()> InOnConfirm, TFunction<void()> InOnCancel)
{
	Title->SetText(InTitle);
	Description->SetText(InMessage);

	ConfirmLabel->SetText(InConfirmText);

	if (InCancelText.IsEmpty())
	{
		CancelButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		CancelLabel->SetText(InCancelText);
	}

	ConfirmButton->OnClicked.AddDynamic(this, &ThisClass::OnConfirmButtonClicked);
	CancelButton->OnClicked.AddDynamic(this, &ThisClass::OnCancelButtonClicked);

	OnConfirm = InOnConfirm;
	OnCancel = InOnCancel;
}

void UConfirmationDialog::SetupDialog(FText InTitle, FText InMessage, FText InConfirmText, TFunction<void()> InOnConfirm)
{
	SetupDialog(InTitle, InMessage, InConfirmText, FText::GetEmpty(), InOnConfirm, 0);
}

void UConfirmationDialog::OnConfirmButtonClicked()
{
	if (OnConfirm)
	{
		OnConfirm();
	}

	RemoveFromParent();
}

void UConfirmationDialog::OnCancelButtonClicked()
{
	if (OnCancel)
	{
		OnCancel();
	}

	RemoveFromParent();
}
