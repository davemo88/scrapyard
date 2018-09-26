// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RobotPartHelper.generated.h"

class URobotPart;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotPartHelper : public UObject
{
  GENERATED_BODY()

public:

  static ARobotPartCardActor* SpawnRobotPartCardActor(
    UWorld* World,
    TSubclassOf<URobotPart> RobotPartClass,
    FVector Loc = FVector(0.0f, 0.0f, 0.0f),
    FRotator Rot = FRotator(0.0f, 0.0f, 0.0f),
    FActorSpawnParameters SpawnParams = FActorSpawnParameters()
  );

};
