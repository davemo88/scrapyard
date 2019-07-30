// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/PartAssignment.h"
#include "Robots/RobotStats.h"
#include "Player/MenuPlayerController.h"
#include "GaragePlayerController.generated.h"

class UGarageWidget;
class UPartCardWidget;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AGaragePlayerController : public AMenuPlayerController
{
  GENERATED_BODY()

public:

  AGaragePlayerController();

  UFUNCTION()
  void GotoGarageTestLevel();

protected:

  UPROPERTY()
  UPartAssignment* PartAssignment;

  UGarageWidget* GarageWidget;

  virtual void SetupWidget() override;

  UFUNCTION()
  void OnPartAssigned(URobotPart* Part);
};
