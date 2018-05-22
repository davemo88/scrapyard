// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARDCLIENT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	virtual void NativeConstruct() override;

public:	

	UFUNCTION(BlueprintCallable)
	void OnGarageButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnHostButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnDraftButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnQuitButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnJoinButtonClicked();
};
