// Fill out your copyright notice in the Description page of Project Settings.

#include "CorePart.h"
#include "PartAssignment.h"
#include "SoloDraft.h"

void UCorePart::Draft(USoloDraft* SoloDraft)
{
//	SoloDraft->DraftedCores.AddUnique(this);
	SoloDraft->DraftedCores.AddUnique(this);
}

void UCorePart::Assign(UPartAssignment* PartAssignment)
{
  PartAssignment->SetCore(this);
}

TSoftObjectPtr<UTexture2D> UCorePart::GetCardIconAssetPtr()
{
  return (PartAssetsBP != NULL) ? PartAssetsBP->CoreCardIcon: nullptr;
}

TArray<FStatText> UCorePart::GetStatsText()
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "PowerSupplyStatText","Power Supply"),FText::AsNumber(PowerSupply)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "BoosterThrustStatText","Booster Thrust"),FText::AsNumber(BoosterThrust)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "BoosterPowerDrainStatText","Booster Power Drain"),FText::AsNumber(BoosterPowerDrain)));
  return StatsText;
}
