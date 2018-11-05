// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RobotStats.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRobotStatsUpdatedDelegate);

class URobotPartAssignment;
struct FStatText;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotStats : public UObject
{
  GENERATED_BODY()

protected:

  URobotPartAssignment* PartAssignment;

public:

  void SetPartAssignment(URobotPartAssignment* NewPartAssignment);

  UFUNCTION()
  void UpdateStats();

  void ZeroStats();

  TMap<FString, FText> GetRobotStatValues();
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 Mass = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 HitPoints = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 MaxPower = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 PowerDrain = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 PhysicalDefense = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 EnergyDefense = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 TargetingAbility = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 ChipSlots = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 WeaponDexterity = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 PowerSupply = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 BoosterThrust = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 BoosterPowerDrain = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 MovementSpeed = 0;

  FStatText GetMassStatText();
  FStatText GetHitPointsStatText();
  FStatText GetMaxPowerStatText();
  FStatText GetPowerDrainStatText();
  FStatText GetPhysicalDefenseStatText();
  FStatText GetEnergyDefenseStatText();
  FStatText GetTargetingAbilityStatText();
  FStatText GetChipSlotsStatText();
  FStatText GetWeaponDexterityStatText();
  FStatText GetPowerSupplyStatText();
  FStatText GetBoosterThrustStatText();
  FStatText GetBoosterPowerDrainStatText();
  FStatText GetMovementSpeedStatText();

  FRobotStatsUpdatedDelegate RobotStatsUpdatedDelegate;
};
