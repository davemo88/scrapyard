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

protected:
  virtual void BeginPlay() override;

  virtual void SetupInputComponent() override;

  UPROPERTY()
  UEscapeMenuWidget* EscapeMenuWidget;

  void ToggleEscapeMenu();
  

};
