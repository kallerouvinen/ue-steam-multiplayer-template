// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "UObject/NoExportTypes.h"
#include "SessionData.generated.h"

/**
 *
 */
UCLASS()
class USessionData : public UObject
{
	GENERATED_BODY()

public:
	void SetSearchResult(const FOnlineSessionSearchResult& InSearchResult) { SearchResult = InSearchResult; }
	FOnlineSessionSearchResult GetSearchResult() const { return SearchResult; }

private:
	FOnlineSessionSearchResult SearchResult;
};
