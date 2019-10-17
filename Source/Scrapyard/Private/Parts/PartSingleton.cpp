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
#include "Parts/BoosterPart.h"
#include "Parts/HandheldPart.h"
#include "Abilities/HitscanAbility.h"
#include "Abilities/ProjectileAbility.h"
#include "Parts/Manufacturer.h"

void UPartSingleton::Init()
{
  InitManufacturers();
  InitPartDB();
}

void UPartSingleton::InitManufacturers()
{
  DefaultManufacturer = NewObject<UManufacturer>();
  DefaultManufacturer->ManufacturerName = NSLOCTEXT("SY", "DefaultCorpName", "Corp");
  DefaultManufacturer->MiniCard = UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->DefaultMiniCard);

  RedManufacturer = NewObject<UManufacturer>();
  RedManufacturer->ManufacturerName = NSLOCTEXT("SY", "RedCorpName", "Red Corp");
  RedManufacturer->Card = UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->RedCard);
  RedManufacturer->MiniCard = UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->RedMiniCard);

  BlueManufacturer = NewObject<UManufacturer>();
  BlueManufacturer->ManufacturerName = NSLOCTEXT("SY", "BlueCorpName", "Blue Corp");
  BlueManufacturer->Card = UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BlueCard);
  BlueManufacturer->MiniCard = UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BlueMiniCard);

  GreenManufacturer = NewObject<UManufacturer>();
  GreenManufacturer->ManufacturerName = NSLOCTEXT("SY", "GreenCorpName", "Green Corp");
  GreenManufacturer->Card = UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->GreenCard);
  GreenManufacturer->MiniCard = UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->GreenMiniCard);

  OrangeManufacturer = NewObject<UManufacturer>();
  OrangeManufacturer->ManufacturerName = NSLOCTEXT("SY", "OrangeCorpName", "Orange Corp");
  OrangeManufacturer->Card = UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->OrangeCard);
  OrangeManufacturer->MiniCard = UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->OrangeMiniCard);

  PurpleManufacturer = NewObject<UManufacturer>();
  PurpleManufacturer->ManufacturerName = NSLOCTEXT("SY", "PurpleCorpName", "Purple Corp");
  PurpleManufacturer->Card = UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->PurpleCard);
  PurpleManufacturer->MiniCard = UScrapyardGameInstance::AssetsBP->GetAsset<UTexture2D>(
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->PurpleMiniCard);
}

void UPartSingleton::InitPartDB()
{
  InitDefaultParts();
  InitRedParts();
  InitBlueParts();
  InitGreenParts();
  InitOrangeParts();
  InitPurpleParts();
}

void UPartSingleton::InitDefaultParts()
{
  PartDB.AddPart(
    UHeadPart::NewHead(
      1000,
      NSLOCTEXT("SY", "DefaultHeadName", "Head"),
      DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->HeadPart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->DefaultMaterial,
      10,
      1));
  PartDB.AddPart(
    UCorePart::NewCore(
      2000,
      NSLOCTEXT("SY", "DefaultCoreName", "Core"),
      DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->CorePart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->DefaultMaterial,
      1000,
      500));
  PartDB.AddPart(
    UArmsPart::NewArms(
      3000,
      NSLOCTEXT("SY", "DefaultArmsName", "Arms"),
      DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->ArmsPart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->DefaultMaterial));
  PartDB.AddPart(
    ULegsPart::NewLegs(
      4000,
      NSLOCTEXT("SY", "DefaultLegsName", "Legs"),
      DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->LegsPart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->DefaultMaterial,
      1000,
      500,
      10,
      100));
  PartDB.AddPart(
    UBoosterPart::NewBooster(
      5000,
      NSLOCTEXT("SY", "DefaultBoosterName", "Booster"),
      DefaultManufacturer,
      nullptr,
      100,
      25,
      100,
      4,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BoosterPart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->DefaultMaterial));
  PartDB.AddPart(
    UHandheldPart::NewHandheld(
      6000,
      NSLOCTEXT("SY", "DefaultHandheldName", "Handheld"),
      DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      0.5f,
      AHitscanAbility::StaticClass(),
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->HandheldPart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->DefaultMaterial));
}

void UPartSingleton::InitRedParts()
{
  PartDB.AddPart(
    UHeadPart::NewHead(
      1001,
      NSLOCTEXT("SY", "RedHeadName", "Red Head"),
      RedManufacturer,
      nullptr,
      100,
      50,
      130,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->HeadPart_Red_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->RedMaterial,
      100,
      0));
  PartDB.AddPart(
    UCorePart::NewCore(
      2001,
      NSLOCTEXT("SY", "RedCoreName", "Red Core"),
      RedManufacturer,
      nullptr,
      100,
      50,
      130,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->CorePart_Red_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->RedMaterial,
      1000,
      1000));
  PartDB.AddPart(
    UArmsPart::NewArms(
      3001,
      NSLOCTEXT("SY", "RedArmsName", "Red Arms"),
      RedManufacturer,
      nullptr,
      100,
      50,
      130,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->ArmsPart_Red_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->RedMaterial));
  PartDB.AddPart(
    ULegsPart::NewLegs(
      4001,
      NSLOCTEXT("SY", "RedLegsName", "Red Legs"),
      RedManufacturer,
      nullptr,
      100,
      50,
      130,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->LegsPart_Red_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->RedMaterial,
      2000,
      400,
      0,
      100));
  PartDB.AddPart(
    UBoosterPart::NewBooster(
      5001,
      NSLOCTEXT("SY", "RedBoosterName", "Red Booster"),
      RedManufacturer,
      nullptr,
      100,
      50,
      1500,
      10,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BoosterPart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->RedMaterial));
  PartDB.AddPart(
    UHandheldPart::NewHandheld(
      6001,
      NSLOCTEXT("SY", "RedHandheldName", "Red Handheld"),
      RedManufacturer,
      nullptr,
      100,
      50,
      100,
      0.5f,
      AProjectileAbility::StaticClass(),
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->HandheldPart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->RedMaterial));
}

void UPartSingleton::InitBlueParts()
{
  PartDB.AddPart(
    UHeadPart::NewHead(
      1002,
      NSLOCTEXT("SY", "BlueHeadName", "Blue Head"),
      BlueManufacturer,
      nullptr,
      100,
      50,
      100,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->HeadPart_Blue_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BlueMaterial,
      10,
      0));
  PartDB.AddPart(
    UCorePart::NewCore(
      2002,
      NSLOCTEXT("SY", "BlueCoreName", "Blue Core"),
      BlueManufacturer,
      nullptr,
      100,
      50,
      100,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->CorePart_Blue_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BlueMaterial,
      1000,
      500));
  PartDB.AddPart(
    UArmsPart::NewArms(
      3002,
      NSLOCTEXT("SY", "BlueArmsName", "Blue Arms"),
      BlueManufacturer,
      nullptr,
      100,
      50,
      100,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->ArmsPart_Blue_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BlueMaterial));
  PartDB.AddPart(
    ULegsPart::NewLegs(
      4002,
      NSLOCTEXT("SY", "BlueLegsName", "Blue Legs"),
      BlueManufacturer,
      nullptr,
      100,
      50,
      100,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->LegsPart_Blue_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BlueMaterial,
      1000,
      500,
      10,
      100));
  PartDB.AddPart(
    UBoosterPart::NewBooster(
      5002,
      NSLOCTEXT("SY", "BlueBoosterName", "Blue Booster"),
      BlueManufacturer,
      nullptr,
      100,
      50,
      2000,
      4,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BoosterPart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BlueMaterial));
  PartDB.AddPart(
    UHandheldPart::NewHandheld(
      6002,
      NSLOCTEXT("SY", "BlueHandheldName", "Blue Handheld"),
      BlueManufacturer,
      nullptr,
      100,
      50,
      100,
      1.0f,
      AHitscanAbility::StaticClass(),
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->HandheldPart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BlueMaterial));
}

void UPartSingleton::InitGreenParts()
{
  PartDB.AddPart(
    UHeadPart::NewHead(
      1003,
      NSLOCTEXT("SY", "GreenHeadName", "Green Head"),
      GreenManufacturer,
      nullptr,
      100,
      50,
      100,
      4,
      11,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->HeadPart_Green_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->GreenMaterial,
      10,
      1));
  PartDB.AddPart(
    UCorePart::NewCore(
      2003,
      NSLOCTEXT("SY", "GreenCoreName", "Green Core"),
      GreenManufacturer,
      nullptr,
      100,
      50,
      100,
      8,
      18,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->CorePart_Green_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->GreenMaterial,
      1000,
      500));
  PartDB.AddPart(
    UArmsPart::NewArms(
      3003,
      NSLOCTEXT("SY", "GreenArmsName", "Green Arms"),
      GreenManufacturer,
      nullptr,
      100,
      50,
      100,
      7,
      17,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->ArmsPart_Green_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->GreenMaterial));
  PartDB.AddPart(
    ULegsPart::NewLegs(
      4003,
      NSLOCTEXT("SY", "GreenLegsName", "Green Legs"),
      GreenManufacturer,
      nullptr,
      100,
      50,
      100,
      10,
      13,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->LegsPart_Green_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->GreenMaterial,
      1000,
      500,
      10,
      100));
  PartDB.AddPart(
    UBoosterPart::NewBooster(
      5003,
      NSLOCTEXT("SY", "GreenBoosterName", "Green Booster"),
      GreenManufacturer,
      nullptr,
      100,
      25,
      100,
      4,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BoosterPart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->GreenMaterial));
  PartDB.AddPart(
    UHandheldPart::NewHandheld(
      6003,
      NSLOCTEXT("SY", "GreenHandheldName", "Green Handheld"),
      GreenManufacturer,
      nullptr,
      120,
      55,
      91,
      0.5f,
      AHitscanAbility::StaticClass(),
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->HandheldPart_Green_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->GreenMaterial));
}

void UPartSingleton::InitOrangeParts()
{
  PartDB.AddPart(
    UHeadPart::NewHead(
      1004,
      NSLOCTEXT("SY", "OrangeHeadName", "Orange Head"),
      OrangeManufacturer,
      nullptr,
      100,
      50,
      100,
      7,
      7,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->HeadPart_Orange_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->OrangeMaterial,
      10,
      1));
  PartDB.AddPart(
    UCorePart::NewCore(
      2004,
      NSLOCTEXT("SY", "OrangeCoreName", "Orange Core"),
      OrangeManufacturer,
      nullptr,
      100,
      50,
      100,
      12,
      16,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->CorePart_Orange_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->OrangeMaterial,
      1000,
      500));
  PartDB.AddPart(
    UArmsPart::NewArms(
      3004,
      NSLOCTEXT("SY", "OrangeArmsName", "Orange Arms"),
      OrangeManufacturer,
      nullptr,
      100,
      50,
      100,
      11,
      13,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->ArmsPart_Orange_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->OrangeMaterial));
  PartDB.AddPart(
    ULegsPart::NewLegs(
      4004,
      NSLOCTEXT("SY", "OrangeLegsName", "Orange Legs"),
      OrangeManufacturer,
      nullptr,
      100,
      50,
      100,
      14,
      9,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->LegsPart_Orange_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->OrangeMaterial,
      1000,
      500,
      10,
      100));
  PartDB.AddPart(
    UBoosterPart::NewBooster(
      5004,
      NSLOCTEXT("SY", "OrangeBoosterName", "Orange Booster"),
      OrangeManufacturer,
      nullptr,
      100,
      25,
      100,
      4,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BoosterPart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->OrangeMaterial));
  PartDB.AddPart(
    UHandheldPart::NewHandheld(
      6004,
      NSLOCTEXT("SY", "OrangeHandheldName", "Orange Handheld"),
      OrangeManufacturer,
      nullptr,
      120,
      55,
      91,
      0.5f,
      AHitscanAbility::StaticClass(),
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->HandheldPart_Orange_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->OrangeMaterial));
}

void UPartSingleton::InitPurpleParts()
{
  PartDB.AddPart(
    UHeadPart::NewHead(
      1005,
      NSLOCTEXT("SY", "PurpleHeadName", "Purple Head"),
      PurpleManufacturer,
      nullptr,
      100,
      50,
      70,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->HeadPart_Purple_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->PurpleMaterial,
      500,
      0));
  PartDB.AddPart(
    UCorePart::NewCore(
      2005,
      NSLOCTEXT("SY", "PurpleCoreName", "Purple Core"),
      PurpleManufacturer,
      nullptr,
      100,
      50,
      70,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->CorePart_Purple_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->PurpleMaterial,
      1500,
      1000));
  PartDB.AddPart(
    UArmsPart::NewArms(
      3005,
      NSLOCTEXT("SY", "PurpleArmsName", "Purple Arms"),
      PurpleManufacturer,
      nullptr,
      100,
      50,
      70,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->ArmsPart_Purple_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->PurpleMaterial));
  PartDB.AddPart(
    ULegsPart::NewLegs(
      4005,
      NSLOCTEXT("SY", "PurpleLegsName", "Purple Legs"),
      PurpleManufacturer,
      nullptr,
      100,
      50,
      70,
      0,
      0,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->LegsPart_Purple_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->PurpleMaterial,
      2000,
      700,
      0,
      200));
  PartDB.AddPart(
    UBoosterPart::NewBooster(
      5005,
      NSLOCTEXT("SY", "PurpleBoosterName", "Purple Booster"),
      PurpleManufacturer,
      nullptr,
      100,
      50,
      2700,
      5,
      nullptr,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->BoosterPart_Default_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->PurpleMaterial));
  PartDB.AddPart(
    UHandheldPart::NewHandheld(
      6005,
      NSLOCTEXT("SY", "PurpleHandheldName", "Purple Handheld"),
      PurpleManufacturer,
      nullptr,
      100,
      50,
      100,
      1.0f,
      AHitscanAbility::StaticClass(),
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->HandheldPart_Purple_SkeletalMesh,
      UScrapyardGameInstance::AssetsBP->PartAssetsBP->PurpleMaterial));
}


