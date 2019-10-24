// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RobotStats.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRobotStatsUpdatedDelegate);

class UPartAssignment;
struct FStatText;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotStats : public UObject
{
  GENERATED_BODY()

public:

  void SetPartAssignment(UPartAssignment* NewPartAssignment);

  UFUNCTION()
  void UpdateStats();
  
  UPROPERTY(EditAnywhere)
  int32 Mass = 0;
  UPROPERTY(EditAnywhere)
// TODO: should be MaxHitPoints
  int32 HitPoints = 0;
  UPROPERTY(EditAnywhere)
  int32 MaxPower = 0;
  UPROPERTY(EditAnywhere)
  int32 PowerDrain = 0;
  UPROPERTY(EditAnywhere)
  int32 Armor = 0;
  UPROPERTY(EditAnywhere)
  int32 EMShield = 0;
  UPROPERTY(EditAnywhere)
  int32 TargetingAbility = 0;
  UPROPERTY(EditAnywhere)
  int32 ChipSlots = 0;
  UPROPERTY(EditAnywhere)
  int32 WeaponDexterity = 0;
  UPROPERTY(EditAnywhere)
  int32 PowerSupply = 0;
  UPROPERTY(EditAnywhere)
  int32 BoosterThrust = 0;
  UPROPERTY(EditAnywhere)
  int32 BoosterPowerDrain = 0;
  UPROPERTY(EditAnywhere)
  int32 MovementSpeed = 0;
  UPROPERTY(EditAnywhere)
  float TurningSpeed = 0;

  FStatText GetMassStatText();
  FStatText GetHitPointsStatText();
  FStatText GetMaxPowerStatText();
  FStatText GetPowerDrainStatText();
  FStatText GetArmorStatText();
  FStatText GetEMShieldStatText();
  FStatText GetTargetingAbilityStatText();
  FStatText GetChipSlotsStatText();
  FStatText GetWeaponDexterityStatText();
  FStatText GetPowerSupplyStatText();
  FStatText GetBoosterThrustStatText();
  FStatText GetBoosterPowerDrainStatText();
  FStatText GetMovementSpeedStatText();

  FRobotStatsUpdatedDelegate RobotStatsUpdatedDelegate;

protected:

  UPartAssignment* PartAssignment;

  void ZeroStats();

};
