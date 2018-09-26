// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RobotPartHelper.generated.h"

class URobotPart;
class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class UHandheldPart;

USTRUCT()
struct FRobotPartAssignment {

  GENERATED_BODY()

  UPROPERTY()
  TSubclassOf<UHeadPart> Head;
  UPROPERTY()
  TSubclassOf<UCorePart> Core;
  UPROPERTY()
  TSubclassOf<UArmsPart> Arms;
  UPROPERTY()
  TSubclassOf<ULegsPart> Legs;
  UPROPERTY()
  TSubclassOf<UHandheldPart> RightHandheld;
};

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
