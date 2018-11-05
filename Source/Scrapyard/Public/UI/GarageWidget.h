// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GarageWidget.generated.h"

class USoloDraft;
class UPartCardWidget;
class UYourPartsWidget;
class URobotStatsWidget;
class URobotPart;
class ARobotBodyGarage;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UGarageWidget : public UUserWidget
{
  GENERATED_BODY()

  AGarageLevelScriptActor* GarageLevelScriptActor;

public:
  
  UPROPERTY(meta=(BindWidget))
  URobotStatsWidget* RobotStatsWidget;

  UPROPERTY(meta=(BindWidget))
  UYourPartsWidget* YourPartsWidget;

};
