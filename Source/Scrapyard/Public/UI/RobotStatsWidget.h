// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Robots/RobotStats.h"
#include "RobotStatsWidget.generated.h"

class UStatLineWidget;
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
  
protected:

  void NativeConstruct() override;

  UPROPERTY()
  URobotStats* RobotStats; 

  UFUNCTION()
  void UpdateStats();

  UPROPERTY(meta=(BindWidget))
  UVerticalBox* StatsPanel;
 
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* HitPointsStatLine;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* MassStatLine;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* PowerSupplyStatLine;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* PowerDrainStatLine;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* KineticDefenseStatLine;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* ElectricDefenseStatLine;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* TargetingAbilityStatLine;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* ChipSlotsStatLine;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* WeaponDexterityStatLine;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* BoosterThrustStatLine;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* BoosterPowerDrainStatLine;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* MovementSpeedStatLine;
  
};
