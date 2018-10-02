// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RobotPartHelper.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotPartHelper : public UObject
{
  GENERATED_BODY()

public:

  static ARobotPartActor* SpawnRobotPartActor(
    UWorld* World,
    FVector Loc = FVector(0.0f, 0.0f, 0.0f),
    FRotator Rot = FRotator(0.0f, 0.0f, 0.0f),
    FActorSpawnParameters SpawnParams = FActorSpawnParameters()
  );

  static URobotPartAssets* GetRobotPartAssets(UWorld* World);

};
