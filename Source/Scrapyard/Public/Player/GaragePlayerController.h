// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MenuPlayerController.h"
#include "GaragePlayerController.generated.h"

class UGarageWidget;
class ARobotBodyGarage;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AGaragePlayerController : public AMenuPlayerController
{
  GENERATED_BODY()

protected:

  UGarageWidget* GarageWidget;

  void SetupWidget();

  void OnNewCardReady(CardWidget* CardWidget);
};
