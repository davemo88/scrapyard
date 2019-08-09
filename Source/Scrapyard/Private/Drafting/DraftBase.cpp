// Fill out your copyright notice in the Description page of Project Settings.


#include "DraftBase.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Parts/RobotPart.h"
#include "Parts/PartSingleton.h"
#include "Parts/PartAssets.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/BoosterPart.h"
#include "Parts/ChipPart.h"
#include "Parts/HandheldPart.h"

UDraftBase::UDraftBase()
{
  PartAssignment = CreateDefaultSubobject<UPartAssignment>(TEXT("PartAssignment"));  

  InitRobotPartPool();
}

void UDraftBase::DraftPart(URobotPart* RobotPart)
{
  RobotPart->Draft(this);
  CurrentPick++;
  RobotPartPool.Remove(RobotPart);
}

URobotPart* UDraftBase::SamplePart()
{
// random part
  return RobotPartPool[FMath::RandRange(0, RobotPartPool.Num() - 1)];
}

void UDraftBase::SamplePack()
{
  CurrentPack.Empty();

  URobotPart* PotentialPart;
  while (CurrentPack.Num() < PackSize)
  {
    PotentialPart = SamplePart();
    if (!CurrentPack.Contains(PotentialPart))
    {
      CurrentPack.Add(PotentialPart);
    }
  }
}

void UDraftBase::InitRobotPartPool()
{
  if (UScrapyardGameInstance* GameInstance = UScrapyardGameInstance::GameInstance)
  {
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1001));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2001));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3001));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4001));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5001));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(6001));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(6002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(6003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(6004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(6005));
  }
}

TArray<URobotPart*> UDraftBase::GetAllDraftedParts()
{
  TArray<URobotPart*> AllParts;
  AllParts.Append(DraftedHeads);
  AllParts.Append(DraftedCores);
  AllParts.Append(DraftedArms);
  AllParts.Append(DraftedLegs);
  AllParts.Append(DraftedBoosters);
  AllParts.Append(DraftedHandhelds);
  AllParts.Append(DraftedChips);

  return AllParts;
}
