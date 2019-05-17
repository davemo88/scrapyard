// Fill out your copyright notice in the Description page of Project Settings.


#include "PartSingleton.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
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

  RedManufacturer = NewObject<UManufacturer>();
  RedManufacturer->ManufacturerName = NSLOCTEXT("SY", "RedCorpName", "Red Corp");
//  RedManufacturer->Card = URobotPart::PartAssets->

  BlueManufacturer = NewObject<UManufacturer>();
  BlueManufacturer->ManufacturerName = NSLOCTEXT("SY", "BlueCorpName", "Blue Corp");

  GreenManufacturer = NewObject<UManufacturer>();
  GreenManufacturer->ManufacturerName = NSLOCTEXT("SY", "GreenCorpName", "Green Corp");

  OrangeManufacturer = NewObject<UManufacturer>();
  OrangeManufacturer->ManufacturerName = NSLOCTEXT("SY", "OrangeCorpName", "Orange Corp");

  PurpleManufacturer = NewObject<UManufacturer>();
  PurpleManufacturer->ManufacturerName = NSLOCTEXT("SY", "PurpleCorpName", "Purple Corp");
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

  if (UScrapyardGameInstance::AssetsBP != nullptr)
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
        UScrapyardGameInstance::AssetsBP->PartAssetsBP->HeadPart_Default_SkeletalMesh,
        UScrapyardGameInstance::AssetsBP->PartAssetsBP->DefaultMaterial,
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
        UScrapyardGameInstance::AssetsBP->PartAssetsBP->CorePart_Default_SkeletalMesh,
        UScrapyardGameInstance::AssetsBP->PartAssetsBP->DefaultMaterial,
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
        UScrapyardGameInstance::AssetsBP->PartAssetsBP->ArmsPart_Default_SkeletalMesh,
        UScrapyardGameInstance::AssetsBP->PartAssetsBP->DefaultMaterial));
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
        UScrapyardGameInstance::AssetsBP->PartAssetsBP->LegsPart_Default_SkeletalMesh,
        UScrapyardGameInstance::AssetsBP->PartAssetsBP->DefaultMaterial,
        1000,
        500,
        10));
  
  }

  return DefaultParts;
}


