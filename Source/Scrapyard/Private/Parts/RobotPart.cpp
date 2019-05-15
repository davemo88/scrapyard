// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPart.h"
#include "Parts/PartAssets.h"
#include "Parts/Manufacturer.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Materials/Material.h"
#include "Engine/Texture2D.h"
#include "Engine/SkeletalMesh.h"

UPartAssets* URobotPart::PartAssetsBP = nullptr;

TArray<FStatText> URobotPart::GetStatsText() const
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetStatsText"), *GetName());

  TArray<FStatText> StatsText;
  StatsText.Add(FStatText(NSLOCTEXT("SY", "MassStatText", "Mass"),FText::AsNumber(Mass)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "HitPointsStatText", "Hit Points"),FText::AsNumber(Mass)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "PowerDrainStatText", "Power Drain"),FText::AsNumber(PowerDrain)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "KineticDefenseStatText", "Kinetic Defense"),FText::AsNumber(KineticDefense)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "ElectricDefenseStatText", "Electric Defense"),FText::AsNumber(ElectricDefense)));
  return StatsText;
}
