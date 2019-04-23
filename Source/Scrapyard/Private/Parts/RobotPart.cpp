// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPart.h"
#include "Parts/RobotPartAssets.h"
#include "Parts/Manufacturer.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Materials/Material.h"
#include "Engine/Texture2D.h"
#include "Engine/SkeletalMesh.h"

URobotPartAssets* URobotPart::RobotPartAssetsBP = nullptr;
FManufacturers URobotPart::Manufacturers;
FPartDatabase URobotPart::PartDB;

void URobotPart::InitRobotPartAssetsBP()
{
  FStringClassReference RobotPartAssetsBPClassRef(TEXT("/Game/RobotPartAssetsBP.RobotPartAssetsBP_C"));
  if (UClass* RobotPartAssetsBPClass = RobotPartAssetsBPClassRef.TryLoadClass<URobotPartAssets>())
  {
    RobotPartAssetsBP = RobotPartAssetsBPClass->GetDefaultObject<URobotPartAssets>();
    if (RobotPartAssetsBP)
    {
      UE_LOG(LogTemp, Warning, TEXT("RobotPartAssetsBP was loaded"));
// TODO: this is a hack since getting game instance outside of actor is mysterious
//      RobotPartAssetsBP->GameInstance = this;
    }
    else
    {
      UE_LOG(LogTemp, Warning, TEXT("RobotPartAssetsBP was NOT loaded"));
    }
  }
}

void URobotPart::InitPartDB()
{
  InitManufacturers();  
  PartDB = FPartDatabase();
  PartDB.AddPart(
    UHeadPart::NewHead(
      1000,
      NSLOCTEXT("SY", "DefaultHeadName", "Default Head"),
      Manufacturers.DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      nullptr,
      URobotPart::RobotPartAssetsBP->HeadPart_Default_SkeletalMesh,
      URobotPart::RobotPartAssetsBP->DefaultMaterial,
      10,
      1));
  PartDB.AddPart(
    UCorePart::NewCore(
      2000,
      NSLOCTEXT("SY", "DefaultCoreName", "Default Core"),
      Manufacturers.DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      nullptr,
      URobotPart::RobotPartAssetsBP->CorePart_Default_SkeletalMesh,
      URobotPart::RobotPartAssetsBP->DefaultMaterial,
      1000,
      500,
      500,
      10));
  PartDB.AddPart(
    UArmsPart::NewArms(
      3000,
      NSLOCTEXT("SY", "DefaultArmsName", "Default Arms"),
      Manufacturers.DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      nullptr,
      URobotPart::RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh,
      URobotPart::RobotPartAssetsBP->DefaultMaterial));
  PartDB.AddPart(
    ULegsPart::NewLegs(
      4000,
      NSLOCTEXT("SY", "DefaultLegsName", "Default Legs"),
      Manufacturers.DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      nullptr,
      URobotPart::RobotPartAssetsBP->LegsPart_Default_SkeletalMesh,
      URobotPart::RobotPartAssetsBP->DefaultMaterial,
      1000,
      500,
      10));

}

void URobotPart::InitManufacturers()
{
  Manufacturers = FManufacturers();
}

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
