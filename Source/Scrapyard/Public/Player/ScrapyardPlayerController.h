// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/EscapeMenuWidget.h"
#include "ScrapyardPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AScrapyardPlayerController : public APlayerController
{
  GENERATED_BODY()

public:

  AScrapyardPlayerController();

  UPROPERTY()
  UEscapeMenuWidget* EscapeMenuWidget;

protected:

  virtual void BeginPlay() override;

  virtual void SetupInputComponent() override;

//NOTE: keep track of default in case it changes, e.g. for ESC menu. maybe a better way?
  bool bDefaultShowMouseCursor;

//  void SetDefaultMouseBehavior();

  void ToggleEscapeMenu();
  virtual void ShowEscapeMenu();
  virtual void HideEscapeMenu();

  void SetEscapeMenuInputMode();

  virtual void SetDefaultInputMode();

};
