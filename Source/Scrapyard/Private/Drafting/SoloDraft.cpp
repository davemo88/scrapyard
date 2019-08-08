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
