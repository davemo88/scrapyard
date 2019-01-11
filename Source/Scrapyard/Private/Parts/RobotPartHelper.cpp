// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartHelper.h"
#include "Game/ScrapyardGameInstance.h"
#include "Parts/RobotPart.h"
#include "Parts/Arms/ArmsPart_Red.h"
#include "Parts/Arms/ArmsPart_Blue.h"
#include "Parts/Arms/ArmsPart_Green.h"
#include "Parts/Arms/ArmsPart_Orange.h"
#include "Parts/Arms/ArmsPart_Purple.h"
#include "AssetRegistryModule.h"
#include "EngineUtils.h"

ARobotPartActor* URobotPartHelper::SpawnRobotPartActor(UWorld* World, FVector Loc, FRotator Rot, FActorSpawnParameters SpawnParams)
{
  if (World)
  {
    ARobotPartActor* RobotPartActor = World->SpawnActor<ARobotPartActor>(Loc, Rot, SpawnParams);
    return RobotPartActor;
  }
  return nullptr;
}

URobotPartAssets* URobotPartHelper::GetRobotPartAssets(UWorld* World)
{
  UE_LOG(LogTemp, Warning, TEXT("URobotPartHelper::GetRobotPartAssets"));
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

TMap<uint32, TSubclassOf<URobotPart>> URobotPartHelper::GetPartDatabase()
{
  TMap<uint32, TSubclassOf<URobotPart>> PartDB;

  PartDB.Add(UArmsPart_Red::PartID, UArmsPart_Blue::StaticClass());
  PartDB.Add(UArmsPart_Blue::PartID, UArmsPart_Blue::StaticClass());
  PartDB.Add(UArmsPart_Green::PartID, UArmsPart_Blue::StaticClass());
  PartDB.Add(UArmsPart_Orange::PartID, UArmsPart_Blue::StaticClass());
  PartDB.Add(UArmsPart_Purple::PartID, UArmsPart_Blue::StaticClass());

  return PartDB;
}
