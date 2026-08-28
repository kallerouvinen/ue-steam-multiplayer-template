// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/MainMenu/JoinGame/SessionListEntry.h"
#include "MultiplayerTemplate/Constants.h"
#include "MultiplayerTemplate/MainMenu/JoinGame/SessionData.h"
#include "Components/TextBlock.h"

void USessionListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	// USessionData* ListItem = Cast<USessionData>(ListItemObject);
	// if (!ListItem) return;

	// FOnlineSessionSearchResult SessionResult = ListItem->GetSessionResult().OnlineResult;

	// FString SessionNameString;
	// if (!SessionResult.Session.SessionSettings.Get(SESSION_NAME_SETTINGS_KEY, SessionNameString))
	// {
	// 	SessionNameString = "Unknown Session";
	// }

	// SessionName->SetText(FText::FromString(SessionNameString));

	// int32 MaxPlayers = SessionResult.Session.SessionSettings.NumPublicConnections;
	// int32 CurrentPlayers = MaxPlayers - SessionResult.Session.NumOpenPublicConnections;
	// FString PlayerCountString = FString::Printf(TEXT("%d/%d"), CurrentPlayers, MaxPlayers);
	// PlayerCount->SetText(FText::FromString(PlayerCountString));
}

void USessionListEntry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	// SessionName->SetColorAndOpacity(bIsSelected ? SelectedColor : DefaultColor);
	// PlayerCount->SetColorAndOpacity(bIsSelected ? SelectedColor : DefaultColor);
}
