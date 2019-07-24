// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Player/ScrapyardPlayerController.h"
#include "MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AMenuPlayerController : public AScrapyardPlayerController
{
  GENERATED_BODY()

public:
  AMenuPlayerController();

  void PostInitializeComponents() override;

  void BeginPlay() override;

  virtual void SetupWidget() {};

  FOnWidgetReadyDelegate OnWidgetReadyDelegate;

  virtual void ShowEscapeMenu() override;
  virtual void HideEscapeMenu() override;
};
