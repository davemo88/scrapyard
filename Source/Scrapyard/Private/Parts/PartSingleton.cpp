// Fill out your copyright notice in the Description page of Project Settings.


#include "PartSingleton.h"
#include "Parts/PartAssets.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/Manufacturer.h"

void UPartSingleton::Init()
{
  InitManufacturers();
  InitPartDB();
}

void UPartSingleton::InitManufacturers()
{
  DefaultManufacturer = NewObject<UManufacturer>();
  DefaultManufacturer->ManufacturerName = NSLOCTEXT("SY", "DefaultCorpName", "Default Corp");
  DefaultManufacturer->CardBackgroundColor = FLinearColor(0.43f, 0.43f, 43.0f, 1.0f);

  RedManufacturer = NewObject<UManufacturer>();
  RedManufacturer->ManufacturerName = NSLOCTEXT("SY", "RedCorpName", "Red Corp");
  RedManufacturer->CardBackgroundColor = FLinearColor(385.0f, 0.0f, 0.0f, 1.0f);

  BlueManufacturer = NewObject<UManufacturer>();
  BlueManufacturer->ManufacturerName = NSLOCTEXT("SY", "BlueCorpName", "Blue Corp");
  BlueManufacturer->CardBackgroundColor = FLinearColor(0.0f, 0.0f, 500.0f, 1.0f);

  GreenManufacturer = NewObject<UManufacturer>();
  GreenManufacturer->ManufacturerName = NSLOCTEXT("SY", "GreenCorpName", "Green Corp");
  GreenManufacturer->CardBackgroundColor = FLinearColor(0.0f, 385.0f, 0.0f, 1.0f);

  OrangeManufacturer = NewObject<UManufacturer>();
  OrangeManufacturer->ManufacturerName = NSLOCTEXT("SY", "OrangeCorpName", "Orange Corp");
  OrangeManufacturer->CardBackgroundColor = FLinearColor(1.0f, 0.29f, 0.0f, 1.0f);

  PurpleManufacturer = NewObject<UManufacturer>();
  PurpleManufacturer->ManufacturerName = NSLOCTEXT("SY", "PurpleCorpName", "Purple Corp");
  PurpleManufacturer->CardBackgroundColor = FLinearColor(1.0f, 0.0f, 72.0f, 1.0f);
}

void UPartSingleton::InitPartDB()
{
  TArray<URobotPart*> DefaultParts = GetDefaultParts();
  for (URobotPart* Part : DefaultParts)
  {
    PartDB.AddPart(Part);
  }
}

TArray<URobotPart*> UPartSingleton::GetDefaultParts()
{
  TArray<URobotPart*> DefaultParts;

  if (URobotPart::PartAssetsBP != nullptr)
  {
    DefaultParts.Add(
      UHeadPart::NewHead(
        1000,
        NSLOCTEXT("SY", "DefaultHeadName", "Default Head"),
        DefaultManufacturer,
        nullptr,
        100,
        50,
        100,
        nullptr,
        URobotPart::PartAssetsBP->HeadPart_Default_SkeletalMesh,
        URobotPart::PartAssetsBP->DefaultMaterial,
        10,
        1));
    DefaultParts.Add(
      UCorePart::NewCore(
        2000,
        NSLOCTEXT("SY", "DefaultCoreName", "Default Core"),
        DefaultManufacturer,
        nullptr,
        100,
        50,
        100,
        nullptr,
        URobotPart::PartAssetsBP->CorePart_Default_SkeletalMesh,
        URobotPart::PartAssetsBP->DefaultMaterial,
        1000,
        500,
        500,
        3));
    DefaultParts.Add(
      UArmsPart::NewArms(
        3000,
        NSLOCTEXT("SY", "DefaultArmsName", "Default Arms"),
        DefaultManufacturer,
        nullptr,
        100,
        50,
        100,
        nullptr,
        URobotPart::PartAssetsBP->ArmsPart_Default_SkeletalMesh,
        URobotPart::PartAssetsBP->DefaultMaterial));
    DefaultParts.Add(
      ULegsPart::NewLegs(
        4000,
        NSLOCTEXT("SY", "DefaultLegsName", "Default Legs"),
        DefaultManufacturer,
        nullptr,
        100,
        50,
        100,
        nullptr,
        URobotPart::PartAssetsBP->LegsPart_Default_SkeletalMesh,
        URobotPart::PartAssetsBP->DefaultMaterial,
        1000,
        500,
        10));
  
  }

  return DefaultParts;
}


