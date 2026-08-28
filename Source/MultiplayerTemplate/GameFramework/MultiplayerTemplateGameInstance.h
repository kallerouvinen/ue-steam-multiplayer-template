// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "AdvancedSessions/Classes/AdvancedFriendsGameInstance.h"
// #include "FindSessionsCallbackProxy.h"
#include "Engine/GameInstance.h"
#include "MultiplayerTemplateGameInstance.generated.h"

/**
 *
 */
UCLASS()
// class UMultiplayerTemplateGameInstance : public UAdvancedFriendsGameInstance
class UMultiplayerTemplateGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// UFUNCTION(BlueprintImplementableEvent, Category = "MultiplayerTemplate|Session")
	// void CreateSession(const TArray<FSessionPropertyKeyPair>& Settings);
	// // void CreateSession(const FString& ServerName);

	// UFUNCTION(BlueprintImplementableEvent, Category = "MultiplayerTemplate|Session")
	// void FindSessions();

	// UFUNCTION(BlueprintImplementableEvent, Category = "MultiplayerTemplate|Session")
	// void JoinSessionEvent(const FBlueprintSessionResult& Session);
};
