// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MenuPlayerController.h"
#include "MainMenuPlayerController.generated.h"

class UMainMenuWidget;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AMainMenuPlayerController : public AMenuPlayerController
{
  GENERATED_BODY()

protected:

  virtual void BeginPlay() override;

  void SetupMainMenuWidget();

  UMainMenuWidget* MainMenuWidget;
  
};
