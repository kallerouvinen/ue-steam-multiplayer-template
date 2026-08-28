// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HostGameWidget.generated.h"

class UButton;
class UCarouselSelector;
class UEditableText;
class UTextBlock;

UENUM()
enum class ESessionVisibility : uint8
{
	FriendsCanJoin,
	InviteOnly,
};

/**
 *
 */
UCLASS()
class UHostGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UHostGameWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UEditableText> GameNameInput;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCarouselSelector> SessionVisibilitySelector;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> StartGameButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ErrorText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> BackButton;

private:
	UFUNCTION()
	void OnGameNameTextChanged(const FText& Text);
	UFUNCTION()
	void OnStartGameButtonClicked();
	UFUNCTION()
	void OnBackButtonClicked();

	ESessionVisibility GetSelectedSessionVisibility() const;
};
