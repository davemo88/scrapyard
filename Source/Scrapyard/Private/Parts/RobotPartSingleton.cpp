// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPartSingleton.h"
#include "Parts/RobotPartAssets.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/Manufacturer.h"

URobotPartSingleton::URobotPartSingleton()
{
  InitRobotPartAssetsBP();
//NOTE: should this be called inside InitPartDB? ehhh
  InitManufacturers();
  InitPartDB();
}

void URobotPartSingleton::InitRobotPartAssetsBP()
{
  FStringClassReference RobotPartAssetsBPClassRef(TEXT("/Game/RobotPartAssetsBP.RobotPartAssetsBP_C"));
  if (UClass* RobotPartAssetsBPClass = RobotPartAssetsBPClassRef.TryLoadClass<URobotPartAssets>())
  {
    RobotPartAssetsBP = RobotPartAssetsBPClass->GetDefaultObject<URobotPartAssets>();
    if (RobotPartAssetsBP)
    {
      UE_LOG(LogTemp, Warning, TEXT("RobotPartAssetsBP was loaded"));
      URobotPart::RobotPartAssetsBP = RobotPartAssetsBP;
// TODO: this is a hack since getting game instance outside of actor is mysterious
//      RobotPartAssetsBP->GameInstance = this;
    }
    else
    {
      UE_LOG(LogTemp, Warning, TEXT("RobotPartAssetsBP was NOT loaded"));
    }
  }
}

void URobotPartSingleton::InitManufacturers()
{
  DefaultManufacturer = CreateDefaultSubobject<UManufacturer>(TEXT("DefaultManufacturer"));
  DefaultManufacturer->ManufacturerName = NSLOCTEXT("SY", "DefaultCorpName", "Default Corp");
  DefaultManufacturer->CardBackgroundColor = FLinearColor(0.43f, 0.43f, 43.0f, 1.0f);

  RedManufacturer = CreateDefaultSubobject<UManufacturer>(TEXT("RedManufacturer"));
  RedManufacturer->ManufacturerName = NSLOCTEXT("SY", "RedCorpName", "Red Corp");
  RedManufacturer->CardBackgroundColor = FLinearColor(385.0f, 0.0f, 0.0f, 1.0f);

  BlueManufacturer = CreateDefaultSubobject<UManufacturer>(TEXT("BlueManufacturer"));
  BlueManufacturer->ManufacturerName = NSLOCTEXT("SY", "BlueCorpName", "Blue Corp");
  BlueManufacturer->CardBackgroundColor = FLinearColor(0.0f, 0.0f, 500.0f, 1.0f);

  GreenManufacturer = CreateDefaultSubobject<UManufacturer>(TEXT("GreenManufacturer"));
  GreenManufacturer->ManufacturerName = NSLOCTEXT("SY", "GreenCorpName", "Green Corp");
  GreenManufacturer->CardBackgroundColor = FLinearColor(0.0f, 385.0f, 0.0f, 1.0f);

  OrangeManufacturer = CreateDefaultSubobject<UManufacturer>(TEXT("OrangeManufacturer"));
  OrangeManufacturer->ManufacturerName = NSLOCTEXT("SY", "OrangeCorpName", "Orange Corp");
  OrangeManufacturer->CardBackgroundColor = FLinearColor(1.0f, 0.29f, 0.0f, 1.0f);

  PurpleManufacturer = CreateDefaultSubobject<UManufacturer>("PurpleManufacturer");
  PurpleManufacturer->ManufacturerName = NSLOCTEXT("SY", "PurpleCorpName", "Purple Corp");
  PurpleManufacturer->CardBackgroundColor = FLinearColor(1.0f, 0.0f, 72.0f, 1.0f);
}

void URobotPartSingleton::InitPartDB()
{
  TArray<URobotPart*> DefaultParts = GetDefaultParts();
  for (URobotPart* Part : DefaultParts)
  {
    PartDB.AddPart(Part);
  }
}

TArray<URobotPart*> URobotPartSingleton::GetDefaultParts()
{
  TArray<URobotPart*> DefaultParts;

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
      URobotPart::RobotPartAssetsBP->HeadPart_Default_SkeletalMesh,
      URobotPart::RobotPartAssetsBP->DefaultMaterial,
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
      URobotPart::RobotPartAssetsBP->CorePart_Default_SkeletalMesh,
      URobotPart::RobotPartAssetsBP->DefaultMaterial,
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
      URobotPart::RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh,
      URobotPart::RobotPartAssetsBP->DefaultMaterial));
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
      URobotPart::RobotPartAssetsBP->LegsPart_Default_SkeletalMesh,
      URobotPart::RobotPartAssetsBP->DefaultMaterial,
      1000,
      500,
      10));

  return DefaultParts;
}


