// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoinGameWidget.generated.h"

class UButton;
class UCircularThrobber;
class UListView;
class USessionData;

/**
 *
 */
UCLASS()
class UJoinGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UJoinGameWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UListView> SessionList;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCircularThrobber> Loader;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> JoinButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> RefreshButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> BackButton;

private:
	UFUNCTION()
	void OnSessionSelectionChanged(UObject* ListItemObject);
	UFUNCTION()
	void OnJoinButtonClicked();
	UFUNCTION()
	void OnRefreshButtonClicked();
	UFUNCTION()
	void OnBackButtonClicked();

	UFUNCTION()
	void OnFindSessionsCompleted(TArray<USessionData*> SessionData);
};
