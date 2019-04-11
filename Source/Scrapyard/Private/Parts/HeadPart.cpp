// Fill out your copyright notice in the Description page of Project Settings.

#include "HeadPart.h"
#include "RobotPartAssignment.h"
#include "SoloDraft.h"

void UHeadPart::Draft(USoloDraft* SoloDraft)
{
//  SoloDraft->DraftedHeads.AddUnique(this);
  SoloDraft->DraftedHeads.AddUnique(this);
}

void UHeadPart::Assign(URobotPartAssignment* PartAssignment)
{
  PartAssignment->SetHead(this);
}

TSoftObjectPtr<UTexture2D> UHeadPart::GetCardIconAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->HeadCardIcon: nullptr;
}

TArray<FStatText> UHeadPart::GetStatsText() const
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "TargetingAbilityStatText","Targeting Ability"),FText::AsNumber(TargetingAbility)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "ChipSlots","Chip Slots"),FText::AsNumber(ChipSlots)));
  return StatsText;
}
