// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPart.h"
#include "Parts/RobotPartAssets.h"
#include "Parts/Manufacturer/Manufacturer_Default.h"
#include "Parts/Manufacturer/Manufacturer_Red.h"
#include "Parts/Manufacturer/Manufacturer_Blue.h"
#include "Parts/Manufacturer/Manufacturer_Green.h"
#include "Parts/Manufacturer/Manufacturer_Purple.h"
#include "Parts/Manufacturer/Manufacturer_Orange.h"
#include "Materials/Material.h"
#include "Engine/Texture2D.h"
#include "Engine/SkeletalMesh.h"

URobotPartAssets* URobotPart::RobotPartAssetsBP = nullptr;

static URobotPart* URobotPart::GetPart(uint32 PartID)
{
  static TArray<uint32, URobotPart*> PartDB = InitPartDB();
  return PartDB.Find(PartID);
}

TArray<uint32, URobotPart*> URobotPart::InitPartDB()
{
  TArray<uint32, URobotPart*> PartDB;
  return PartDB;
}

USkeletalMesh* URobotPart::GetSkeletalMesh()
{
  if (SkeletalMesh->IsValid())
  {
    return SkeletalMesh.Get();
  }
  else if (SkeletalMesh->IsPending())
  {
    return SkeletalMesh->LoadSynchronous();
  }
  return nullptr;
}

UMaterial* URobotPart::GetMajorMaterial()
{
  if (MajorMaterial->IsValid())
  {
    return MajorMaterial.Get();
  }
  else if (MajorMaterial->IsPending())
  {
    return MajorMaterial->LoadSynchronous();
  }
  return nullptr;
}

TArray<FStatText> URobotPart::GetStatsText() const
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetStatsText"), *GetName());

  TArray<FStatText> StatsText;
  StatsText.Add(FStatText(NSLOCTEXT("SY", "MassStatText", "Mass"),FText::AsNumber(Mass)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "HitPointsStatText", "Hit Points"),FText::AsNumber(Mass)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "PowerDrainStatText", "Power Drain"),FText::AsNumber(PowerDrain)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "PhysicalDefenseStatText", "Physical Defense"),FText::AsNumber(PhysicalDefense)));
  StatsText.Add(FStatText(NSLOCTEXT("SY", "EnergyDefenseStatText", "Energy Defense"),FText::AsNumber(EnergyDefense)));
  return StatsText;
}
