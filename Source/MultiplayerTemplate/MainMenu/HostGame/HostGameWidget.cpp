// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/MainMenu/HostGame/HostGameWidget.h"
#include "MultiplayerTemplate/Constants.h"
#include "MultiplayerTemplate/GameFramework/SteamMultiplayerSubsystem.h"
#include "MultiplayerTemplate/UI/CarouselSelector.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UHostGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameNameInput->OnTextChanged.AddDynamic(this, &ThisClass::OnGameNameTextChanged);
	StartGameButton->OnClicked.AddDynamic(this, &ThisClass::OnStartGameButtonClicked);
	BackButton->OnClicked.AddDynamic(this, &ThisClass::OnBackButtonClicked);
}

void UHostGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USteamMultiplayerSubsystem* SteamMPSubsystem = GameInstance->GetSubsystem<USteamMultiplayerSubsystem>())
		{
			const FString DefaultSessionName = GameInstance->GetSubsystem<USteamMultiplayerSubsystem>()->GetDefaultSessionName();
			FText DefaultSessionNameText = FText::FromString(DefaultSessionName);
			GameNameInput->SetText(DefaultSessionNameText);
			OnGameNameTextChanged(DefaultSessionNameText);
			return;
		}
	}

	OnGameNameTextChanged(FText::GetEmpty());
}

void UHostGameWidget::OnGameNameTextChanged(const FText& Text)
{
	bool bHasValidText = !Text.IsEmptyOrWhitespace();

	ErrorText->SetText(bHasValidText
					? FText::GetEmpty()
					: FText::FromString(TEXT("Game name cannot be empty.")));

	StartGameButton->SetIsEnabled(bHasValidText);
}

void UHostGameWidget::OnStartGameButtonClicked()
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USteamMultiplayerSubsystem* SteamMPSubsystem = GameInstance->GetSubsystem<USteamMultiplayerSubsystem>())
		{
			// TODO: Use session settings as parameters
			SteamMPSubsystem->HostSession(
					GameNameInput->GetText().ToString(),
					GetSelectedSessionVisibility());
		}
	}
}

void UHostGameWidget::OnBackButtonClicked()
{
	RemoveFromParent();
}

ESessionVisibility UHostGameWidget::GetSelectedSessionVisibility() const
{
	switch (SessionVisibilitySelector->GetSelectedIndex())
	{
		case 0:
			return ESessionVisibility::Public;
		case 1:
			return ESessionVisibility::FriendsOnly;
		case 2:
		default:
			return ESessionVisibility::InviteOnly;
	}
}
