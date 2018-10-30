// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RobotStatsWidget.generated.h"

class UStatLineWidget;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotStatsWidget : public UUserWidget
{
  GENERATED_BODY()
  
protected:

  UPROPERTY(meta=(BindWidget))
  UVerticalBox* StatsPanel;
 
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* HitPoints;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* Mass;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* EnergySupply;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* EnergyDrain;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* PhysicalDefense;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* EnergyDefense;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* TargetingAbility;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* WeaponDexterity;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* BoosterThrust;
  UPROPERTY(meta=(BindWidget))
  UStatLineWidget* MovementSpeed;

  
};
