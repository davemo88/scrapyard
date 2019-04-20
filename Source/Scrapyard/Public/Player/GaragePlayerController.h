// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPartAssignment.h"
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

protected:

  URobotPartAssignment* PartAssignment;

  UGarageWidget* GarageWidget;

  void SetupWidget();

  UFUNCTION()
  void OnNewCardReady(UPartCardWidget* CardWidget);

  UFUNCTION()
  void OnCardDoubleClicked(URobotPart* RobotPart);

public:

  void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  UFUNCTION()
  void GotoGarageTestLevel();
};
