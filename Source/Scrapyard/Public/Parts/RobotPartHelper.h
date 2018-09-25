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

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotPartHelper : public UObject
{
  GENERATED_BODY()

public:

//  URobotPartHelper();
  
private:

  static const FString HeadPath;
  static const FString CorePath;
  static const FString ArmsPath;
  static const FString LegsPath;


  template <typename T>
  static TArray<T*> GetAllPartsInFolder(FString Path);

public:

  static TArray<UHeadPart*> GetAllHeads();
  static TArray<UCorePart*> GetAllCores();
  static TArray<UArmsPart*> GetAllArms();
  static TArray<ULegsPart*> GetAllLegs();

  static ARobotPartCardActor* SpawnRobotPartCardActor(
    UWorld* World,
    TSubclassOf<URobotPart> RobotPartClass,
    FVector Loc = FVector(0.0f, 0.0f, 0.0f),
    FRotator Rot = FRotator(0.0f, 0.0f, 0.0f),
    FActorSpawnParameters SpawnParams = FActorSpawnParameters()
  );



};
