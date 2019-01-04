// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Online/ScrapyardGameSession.h"
#include "UI/HostEntryWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UMainMenuWidget : public UUserWidget
{
  GENERATED_BODY()

protected:

  virtual void NativeConstruct() override;

  UPROPERTY(meta=(BindWidget))
  UButton* DraftButton;
  UPROPERTY(meta=(BindWidget))
  UButton* GarageButton;
  UPROPERTY(meta=(BindWidget))
  UButton* JoinButton;
  UPROPERTY(meta=(BindWidget))
  UButton* HostButton;
  UPROPERTY(meta=(BindWidget))
  UButton* QuitButton;

  UPROPERTY(meta=(BindWidget))
  UHostEntryWidget* HostEntryWidget;

//TODO: get rid of blueprint logic
  UFUNCTION()
  void OnDraftButtonClicked();
  UFUNCTION()
  void OnGarageButtonClicked();
  UFUNCTION()
  void OnHostButtonClicked();
  UFUNCTION()
  void OnJoinButtonClicked();
  UFUNCTION()
  void OnQuitButtonClicked();
};
