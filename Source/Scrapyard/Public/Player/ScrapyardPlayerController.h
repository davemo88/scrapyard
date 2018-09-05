// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ScrapyardPlayerController.generated.h"

class URobotHUDWidget;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AScrapyardPlayerController : public APlayerController
{
  GENERATED_BODY()

protected:
  virtual void BeginPlay() override;

  void SetupRobotHUDWidget();

  URobotHUDWidget* RobotHUDWidget;

};
