// Fill out your copyright notice in the Description page of Project Settings.

#include "LegsPart.h"
#include "Robots/RobotBodyComponent.h"
#include "SoloDraft.h"

void ULegsPart::Draft(USoloDraft* SoloDraft)
{
//  SoloDraft->DraftedLegs.AddUnique(this);
  SoloDraft->DraftedLegs.AddUnique(this);
}

void ULegsPart::Assign(URobotBodyComponent* RobotBody)
{
//  RobotBody->SetLegs(this);
}

TSoftObjectPtr<UTexture2D> ULegsPart::GetCardIconAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->LegsCardIcon: nullptr;
}

TArray<FStatText> ULegsPart::GetStatsText()
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText("Movement Speed",FString::Printf(TEXT("%i"), MovementSpeed)));
  return StatsText;
}
