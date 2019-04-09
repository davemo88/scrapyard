// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartHelper.h"
#include "Game/ScrapyardGameInstance.h"
#include "Parts/RobotPart.h"
#include "Parts/Arms/ArmsPart_Default.h"
#include "Parts/Arms/ArmsPart_Red.h"
#include "Parts/Arms/ArmsPart_Blue.h"
#include "Parts/Arms/ArmsPart_Green.h"
#include "Parts/Arms/ArmsPart_Orange.h"
#include "Parts/Arms/ArmsPart_Purple.h"
#include "Parts/Core/CorePart_Default.h"
#include "Parts/Core/CorePart_Red.h"
#include "Parts/Core/CorePart_Blue.h"
#include "Parts/Core/CorePart_Green.h"
#include "Parts/Core/CorePart_Orange.h"
#include "Parts/Core/CorePart_Purple.h"
#include "Parts/Head/HeadPart_Default.h"
#include "Parts/Head/HeadPart_Red.h"
#include "Parts/Head/HeadPart_Blue.h"
#include "Parts/Head/HeadPart_Green.h"
#include "Parts/Head/HeadPart_Orange.h"
#include "Parts/Head/HeadPart_Purple.h"
#include "Parts/Legs/LegsPart_Default.h"
#include "Parts/Legs/LegsPart_Red.h"
#include "Parts/Legs/LegsPart_Blue.h"
#include "Parts/Legs/LegsPart_Green.h"
#include "Parts/Legs/LegsPart_Orange.h"
#include "Parts/Legs/LegsPart_Purple.h"
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

// TODO: build this database once initially and save as file
// only need to update when new parts are released
  PartDB.Add(UArmsPart_Default::PartID, UArmsPart_Default::StaticClass());
  PartDB.Add(UArmsPart_Red::PartID, UArmsPart_Red::StaticClass());
  PartDB.Add(UArmsPart_Blue::PartID, UArmsPart_Blue::StaticClass());
  PartDB.Add(UArmsPart_Green::PartID, UArmsPart_Green::StaticClass());
  PartDB.Add(UArmsPart_Orange::PartID, UArmsPart_Orange::StaticClass());
  PartDB.Add(UArmsPart_Purple::PartID, UArmsPart_Purple::StaticClass());
  PartDB.Add(UCorePart_Default::PartID, UCorePart_Default::StaticClass());
  PartDB.Add(UCorePart_Red::PartID, UCorePart_Red::StaticClass());
  PartDB.Add(UCorePart_Blue::PartID, UCorePart_Blue::StaticClass());
  PartDB.Add(UCorePart_Green::PartID, UCorePart_Green::StaticClass());
  PartDB.Add(UCorePart_Orange::PartID, UCorePart_Orange::StaticClass());
  PartDB.Add(UCorePart_Purple::PartID, UCorePart_Purple::StaticClass());
  PartDB.Add(UHeadPart_Default::PartID, UHeadPart_Default::StaticClass());
  PartDB.Add(UHeadPart_Red::PartID, UHeadPart_Red::StaticClass());
  PartDB.Add(UHeadPart_Blue::PartID, UHeadPart_Blue::StaticClass());
  PartDB.Add(UHeadPart_Green::PartID, UHeadPart_Green::StaticClass());
  PartDB.Add(UHeadPart_Orange::PartID, UHeadPart_Orange::StaticClass());
  PartDB.Add(UHeadPart_Purple::PartID, UHeadPart_Purple::StaticClass());
  PartDB.Add(ULegsPart_Default::PartID, ULegsPart_Default::StaticClass());
  PartDB.Add(ULegsPart_Red::PartID, ULegsPart_Red::StaticClass());
  PartDB.Add(ULegsPart_Blue::PartID, ULegsPart_Blue::StaticClass());
  PartDB.Add(ULegsPart_Green::PartID, ULegsPart_Green::StaticClass());
  PartDB.Add(ULegsPart_Orange::PartID, ULegsPart_Orange::StaticClass());
  PartDB.Add(ULegsPart_Purple::PartID, ULegsPart_Purple::StaticClass());

  return PartDB;
}
