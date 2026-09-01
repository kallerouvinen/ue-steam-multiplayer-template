// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class ESessionVisibility : uint8
{
	Public UMETA(DisplayName = "Public"),
	FriendsOnly UMETA(DisplayName = "Friends Only"),
	InviteOnly UMETA(DisplayName = "Invite Only"),
};
