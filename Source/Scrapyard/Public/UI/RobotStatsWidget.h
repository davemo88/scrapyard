// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Robots/RobotStats.h"
#include "RobotStatsWidget.generated.h"

class URobotStatLineWidget;
class UVerticalBox;
class UButton;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotStatsWidget : public UUserWidget
{
  GENERATED_BODY()

public:

  void SetRobotStats(URobotStats* NewRobotStats); 

  void SetNewValueStats(URobotStats* NewRobotStats);
  
protected:

  void NativeConstruct() override;

  UPROPERTY()
  URobotStats* RobotStats; 

  UPROPERTY()
  URobotStats* NewValueStats; 

  UFUNCTION()
  void UpdateStats();

  UFUNCTION()
  void UpdateNewValues();

  UPROPERTY(meta=(BindWidget))
  UVerticalBox* StatsPanel;
 
  UPROPERTY(meta=(BindWidget))
  URobotStatLineWidget* HitPointsStatLine;
  UPROPERTY(meta=(BindWidget))
  URobotStatLineWidget* MassStatLine;
  UPROPERTY(meta=(BindWidget))
  URobotStatLineWidget* PowerSupplyStatLine;
  UPROPERTY(meta=(BindWidget))
  URobotStatLineWidget* PowerDrainStatLine;
  UPROPERTY(meta=(BindWidget))
  URobotStatLineWidget* ArmorStatLine;
  UPROPERTY(meta=(BindWidget))
  URobotStatLineWidget* EMShieldStatLine;
  UPROPERTY(meta=(BindWidget))
  URobotStatLineWidget* TargetingAbilityStatLine;
  UPROPERTY(meta=(BindWidget))
  URobotStatLineWidget* ChipSlotsStatLine;
  UPROPERTY(meta=(BindWidget))
  URobotStatLineWidget* WeaponDexterityStatLine;
  UPROPERTY(meta=(BindWidget))
  URobotStatLineWidget* BoosterThrustStatLine;
  UPROPERTY(meta=(BindWidget))
  URobotStatLineWidget* BoosterPowerDrainStatLine;
  UPROPERTY(meta=(BindWidget))
  URobotStatLineWidget* MovementSpeedStatLine;
  
};
