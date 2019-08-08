// Fill out your copyright notice in the Description page of Project Settings.

#include "Drafting/SoloDraft.h"
#include "Game/ScrapyardGameInstance.h"
#include "Parts/PartAssignment.h"
#include "Parts/PartSingleton.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/BoosterPart.h"
#include "Parts/ChipPart.h"
#include "Parts/HandheldPart.h"

USoloDraft::USoloDraft()
{
  TotalPicks = 10;
  PackSize = 3;
  
  CurrentPick = 0;
  InitPickTypes();
}

void USoloDraft::InitPickTypes()
{
// guarantee one pick of only parts of each required type
  PickTypes.Add(UHeadPart::StaticClass());
  PickTypes.Add(UCorePart::StaticClass());
  PickTypes.Add(UArmsPart::StaticClass());
  PickTypes.Add(ULegsPart::StaticClass());
  PickTypes.Add(UBoosterPart::StaticClass());
  PickTypes.Add(UHandheldPart::StaticClass());

  while (PickTypes.Num() < TotalPicks)
  {
    PickTypes.Add(URobotPart::StaticClass());
  }
}

void USoloDraft::InitRobotPartPool()
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

TArray<TSubclassOf<URobotPart>> USoloDraft::GetPickTypes()
{
  return PickTypes;
}

URobotPart* USoloDraft::SamplePart(TSubclassOf<URobotPart> PickType);
{
// if a specific part type is given, filter for parts of that type
  if (PickType != URobotPart::StaticClass())
  {
    TArray<URobotPart*> EligibleParts = RobotPartPool.FilterByPredicate([PickType](URobotPart* Part){ return Part->IsA(PickType); }); 

    return EligibleParts[FMath::RandRange(0, RobotPartPool.Num() - 1)];
  }
// otherwise return a random part
  return RobotPartPool[FMath::RandRange(0, RobotPartPool.Num() - 1)];
    
}

TArray<URobotPart*> USoloDraft::SamplePack()
{
  CurrentDraft->CurrentPack.Empty();

  TSubclassOf<URobotPart> PickType = SamplePickType();
  URobotPart* PotentialPart;
  while (CurrentDraft->CurrentPack.Num() < CurrentDraft->PackSize)
  {
    PotentialPart = SamplePart(PickType);
    if (!CurrentDraft->CurrentPack.Contains(PotentialPart))
    {
      CurrentDraft->CurrentPack.Add(PotentialPart);
    }
  }

}

TSubclassOf<URobotPart> USoloDraft::SamplePickType()
{
  TSubclassOf<URobotPart> PickType = PickTypes[FMath::RandRange(0, PickTypes.Num() - 1)];
  PickTypes.RemoveSingle(PickType);
  return PickType;
}
