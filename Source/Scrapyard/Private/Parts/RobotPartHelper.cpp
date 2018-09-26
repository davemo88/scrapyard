// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartHelper.h"
#include "Parts/RobotPartCardActor.h"
#include "AssetRegistryModule.h"
#include "EngineUtils.h"

ARobotPartCardActor* URobotPartHelper::SpawnRobotPartCardActor(UWorld* World, TSubclassOf<URobotPart> RobotPart, FVector Loc, FRotator Rot, FActorSpawnParameters SpawnParams)
{
  if (World)
  {
    ARobotPartCardActor* CardActor = World->SpawnActor<ARobotPartCardActor>(Loc, Rot, SpawnParams);
    CardActor->SetRobotPart(RobotPart);
    return CardActor;
  }
  return nullptr;
}

