// Fill out your copyright notice in the Description page of Project Settings.

#include "LegsPart.h"
#include "RobotPartAssignment.h"
#include "SoloDraft.h"

void ULegsPart::Draft(USoloDraft* SoloDraft)
{
//  SoloDraft->DraftedLegs.AddUnique(this);
  SoloDraft->DraftedLegs.AddUnique(this);
}

void ULegsPart::Assign(URobotPartAssignment* PartAssignment)
{
  PartAssignment->SetLegs(this);
}

TSoftObjectPtr<UTexture2D> ULegsPart::GetCardIconAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->LegsCardIcon: nullptr;
}

TArray<FStatText> ULegsPart::GetStatsText() const
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "MovementSpeedStatText","Movement Speed"),FText::AsNumber(MovementSpeed)));
  return StatsText;
}
