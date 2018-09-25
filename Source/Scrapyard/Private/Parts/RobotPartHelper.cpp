// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartHelper.h"
#include "Parts/RobotPartCardActor.h"
#include "AssetRegistryModule.h"
#include "EngineUtils.h"

// these are useless and wrong now but hey
const FString URobotPartHelper::HeadPath = FString(TEXT("/Game/Parts/Head"));
const FString URobotPartHelper::CorePath = FString(TEXT("/Game/Parts/Core"));
const FString URobotPartHelper::ArmsPath = FString(TEXT("/Game/Parts/Arms"));
const FString URobotPartHelper::LegsPath = FString(TEXT("/Game/Parts/Legs"));

template <typename T>
TArray<T*> URobotPartHelper::GetAllPartsInFolder(FString Path)
{
  TArray<UObject*> Assets;
//  EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Parts/Head"), Assets, EngineUtils::ATL_Regular);
  
  UE_LOG(LogTemp, Warning, TEXT("path is: %s"), *Path);
  bool Result = EngineUtils::FindOrLoadAssetsByPath(Path, Assets, EngineUtils::ATL_Regular);
  if (Result) {
    UE_LOG(LogTemp, Warning, TEXT("got this many assets: %i"), Assets.Num());
  }

  TArray<T*> Parts;
  for (UObject* Asset : Assets)
  {
    T* Part = Cast<T>(Asset);
    if (Part)
    {
      Parts.Add(Part);
    }
    else
    {
      // probably abort cause something's wrong
    }
  }
  UE_LOG(LogTemp, Warning, TEXT("got this many parts: %i"), Parts.Num());

  return Parts;
}

TArray<UHeadPart*> URobotPartHelper::GetAllHeads()
{
  return URobotPartHelper::GetAllPartsInFolder<UHeadPart>(HeadPath);
}

TArray<UCorePart*> URobotPartHelper::GetAllCores()
{
  return URobotPartHelper::GetAllPartsInFolder<UCorePart>(CorePath);
}

TArray<UArmsPart*> URobotPartHelper::GetAllArms()
{
  return URobotPartHelper::GetAllPartsInFolder<UArmsPart>(ArmsPath);
}

TArray<ULegsPart*> URobotPartHelper::GetAllLegs()
{
  return URobotPartHelper::GetAllPartsInFolder<ULegsPart>(LegsPath);
}

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

