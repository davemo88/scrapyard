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
  int32 MaxHitPoints = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 MaxPower = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 PowerDrain = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 PhysicalDefense = 0;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 EnergyDefense = 0;

  FRobotStatsUpdatedDelegate RobotStatsUpdatedDelegate;
};
