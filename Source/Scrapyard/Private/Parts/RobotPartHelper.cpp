// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartHelper.h"
#include "Parts/RobotPartActor.h"
#include "AssetRegistryModule.h"
#include "EngineUtils.h"

ARobotPartActor* URobotPartHelper::SpawnRobotPartActor(UWorld* World, TSubclassOf<URobotPart> RobotPart, FVector Loc, FRotator Rot, FActorSpawnParameters SpawnParams)
{
  if (World)
  {
    ARobotPartActor* RobotPartActor = World->SpawnActor<ARobotPartActor>(Loc, Rot, SpawnParams);
    RobotPartActor->SetRobotPart(RobotPart);
    return RobotPartActor;
  }
  return nullptr;
}

