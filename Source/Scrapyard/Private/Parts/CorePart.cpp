// Fill out your copyright notice in the Description page of Project Settings.

#include "CorePart.h"
#include "RobotPartAssignment.h"
#include "SoloDraft.h"

void UCorePart::Draft(USoloDraft* SoloDraft)
{
//	SoloDraft->DraftedCores.AddUnique(this);
	SoloDraft->DraftedCores.AddUnique(this);
}

void UCorePart::Assign(URobotPartAssignment* PartAssignment)
{
  PartAssignment->SetCore(this);
}

TSoftObjectPtr<UTexture2D> UCorePart::GetCardIconAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->CoreCardIcon: nullptr;
}

TArray<FStatText> UCorePart::GetStatsText()
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "PowerSupplyStatText","Power Supply"),FText::AsNumber(PowerSupply)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "BoosterThrustStatText","Booster Thrust"),FText::AsNumber(BoosterThrust)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "BoosterPowerDrainStatText","Booster Power Drain"),FText::AsNumber(BoosterPowerDrain)));
  return StatsText;
}
