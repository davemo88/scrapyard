// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIAssets.generated.h"

class UMainMenuWidget;
class UEscapeMenuWidget;
class UGarageWidget;
class USoloDraftWidget;
class UPartCardWidget;
class URobotHUDWidget;
class UStatLineWidget;
class UMatchTimerWidget;
class URobotTunerWidget;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UUIAssets : public UObject
{
  GENERATED_BODY()

public:

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class UMainMenuWidget> MainMenuWidgetBP;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class UEscapeMenuWidget> EscapeMenuWidgetBP;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class UGarageWidget> GarageWidgetBP;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class USoloDraftWidget> SoloDraftWidgetBP;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class UPartCardWidget> PartCardWidgetBP;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class URobotHUDWidget> RobotHUDWidgetBP;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class UStatLineWidget> StatLineWidgetBP;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class UMatchTimerWidget> MatchTimerWidgetBP;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class URobotTunerWidget> RobotTunerWidgetBP;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class UTargetingWidget> TargetingWidgetBP;

};
