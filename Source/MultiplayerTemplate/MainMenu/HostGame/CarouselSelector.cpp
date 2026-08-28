// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#include "MultiplayerTemplate/MainMenu/HostGame/CarouselSelector.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

UCarouselSelector::UCarouselSelector(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
{
}

void UCarouselSelector::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	LeftButton->OnClicked.AddDynamic(this, &ThisClass::OnLeftButtonClicked);
	RightButton->OnClicked.AddDynamic(this, &ThisClass::OnRightButtonClicked);
}

int32 UCarouselSelector::GetSelectedIndex() const
{
	return SelectedItemSwitcher->GetActiveWidgetIndex();
}

void UCarouselSelector::OnLeftButtonClicked()
{
	int32 NumItems = SelectedItemSwitcher->GetNumWidgets();
	int32 ActiveIndex = SelectedItemSwitcher->GetActiveWidgetIndex();
	int32 NewActiveIndex = (ActiveIndex - 1 + NumItems) % NumItems;
	SelectedItemSwitcher->SetActiveWidgetIndex(NewActiveIndex);
}

void UCarouselSelector::OnRightButtonClicked()
{
	int32 NumItems = SelectedItemSwitcher->GetNumWidgets();
	int32 ActiveIndex = SelectedItemSwitcher->GetActiveWidgetIndex();
	int32 NewActiveIndex = (ActiveIndex + 1) % NumItems;
	SelectedItemSwitcher->SetActiveWidgetIndex(NewActiveIndex);
}
