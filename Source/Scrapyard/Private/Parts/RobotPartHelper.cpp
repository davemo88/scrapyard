// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartHelper.h"
#include "Parts/RobotPartActor.h"
#include "AssetRegistryModule.h"
#include "EngineUtils.h"

ARobotPartActor* URobotPartHelper::SpawnRobotPartActor(UWorld* World, FVector Loc, FRotator Rot, FActorSpawnParameters SpawnParams)
{
  if (World)
  {
    ARobotPartActor* RobotPartActor = World->SpawnActor<ARobotPartActor>(Loc, Rot, SpawnParams);
    RobotPartActor->SetRobotPart(RobotPart);
    return RobotPartActor;
  }
  return nullptr;
}

URobotPartAssets* URobotPartHelper::GetRobotPartAssets(UWorld* World)
{
  UE_LOG(LogTemp, Warning, TEXT("URobotPartHelper::GetRobotPartAssets"), *GetName());
  if (World)
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(World->GetGameInstance());
    return GameInstance->RobotPartAssetsBP;
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("World was null"));
  }
  return nullptr;
}

