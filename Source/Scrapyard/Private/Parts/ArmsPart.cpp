// Fill out your copyright notice in the Description page of Project Settings.

#include "ArmsPart.h"
#include "RobotPartAssignment.h"
#include "Parts/RobotPartAssets.h"
#include "SoloDraft.h"

void UArmsPart::Draft(USoloDraft* SoloDraft)
{
//  SoloDraft->DraftedArms.AddUnique(this);
//  UE_LOG(LogTemp, Warning, TEXT("Drafted %s"), *PartName);
  SoloDraft->DraftedArms.AddUnique(this);
}

void UArmsPart::Assign(URobotPartAssignment* PartAssignment)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::Assign"), *GetName());
  PartAssignment->SetArms(this);
}

TSoftObjectPtr<UTexture2D> UArmsPart::GetCardIconAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsCardIcon: nullptr;
}

TArray<FStatText> UArmsPart::GetStatsText()
{
  TArray<FStatText> StatsText = Super::GetStatsText();
  StatsText.Add(FStatText(NSLOCTEXT("SY", "WeaponDexterityStatText","Weapon Dexterity"),FText::AsNumber(WeaponDexterity)));
  return StatsText;
}
