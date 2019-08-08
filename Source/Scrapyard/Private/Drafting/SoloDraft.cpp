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

  InitMissingTypes();
}

URobotPart* USoloDraft::SamplePart()
{
// if the player is in danger of missing a part type, only sample the types they are missing
  if (MissingTypes.Num() == TotalPicks - CurrentPick)
  {
    UE_LOG(LogDraft, VeryVerbose, TEXT("Uh oh! missing %i types! to the rescue!"), MissingTypes.Num());
    TArray<URobotPart*> EligibleParts = RobotPartPool.FilterByPredicate([this](URobotPart* Part){ return MissingTypes.Contains(Part->GetClass()); }); 

    return EligibleParts[FMath::RandRange(0, EligibleParts.Num() - 1)];
  }
// otherwise return a random part
  return RobotPartPool[FMath::RandRange(0, RobotPartPool.Num() - 1)];
    
}

void USoloDraft::DraftPart(URobotPart* RobotPart)
{
  if (MissingTypes.Contains(RobotPart->GetClass()))
  {
    MissingTypes.Remove(RobotPart->GetClass());
  }
  Super::DraftPart(RobotPart);
}

void USoloDraft::InitMissingTypes()
{
  MissingTypes.Add(UHeadPart::StaticClass());
  MissingTypes.Add(UCorePart::StaticClass());
  MissingTypes.Add(UArmsPart::StaticClass());
  MissingTypes.Add(ULegsPart::StaticClass());
  MissingTypes.Add(UBoosterPart::StaticClass());
  MissingTypes.Add(UHandheldPart::StaticClass());
}
