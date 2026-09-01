// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/UI/MessageDialog.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UMessageDialog::SetupDialog(FText InTitle, FText InMessage, const FMessageDialogButton& InButton1, const FMessageDialogButton& InButton2)
{
	Title->SetText(InTitle);
	Description->SetText(InMessage);

	Button1Label->SetText(InButton1.Label);
	OnButton1 = InButton1.OnClicked;
	Button1->OnClicked.RemoveAll(this);
	Button1->OnClicked.AddDynamic(this, &ThisClass::OnButton1Clicked);

	if (Button2)
	{
		Button2->OnClicked.RemoveAll(this);

		if (Button2Label && !InButton2.Label.IsEmpty())
		{
			Button2->SetVisibility(ESlateVisibility::Visible);
			Button2Label->SetText(InButton2.Label);
			OnButton2 = InButton2.OnClicked;
			Button2->OnClicked.AddDynamic(this, &ThisClass::OnButton2Clicked);
		}
		else
		{
			Button2->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UMessageDialog::OnButton1Clicked()
{
	if (OnButton1)
	{
		OnButton1();
	}

	RemoveFromParent();
}

void UMessageDialog::OnButton2Clicked()
{
	if (OnButton2)
	{
		OnButton2();
	}

	RemoveFromParent();
}
