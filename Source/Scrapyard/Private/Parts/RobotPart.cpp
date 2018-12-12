// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPart.h"
#include "RobotPartAssets.h"
#include "Engine/SkeletalMesh.h"

URobotPartAssets* URobotPart::RobotPartAssetsBP = nullptr;

URobotPart::URobotPart()
{

}

void URobotPart::PostInitProperties()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::PostInitProperties"), *GetName());
  Super::PostInitProperties();
  SetupAssetAttributes();
}

USkeletalMesh* URobotPart::GetSkeletalMesh()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetSkeletalMesh"), *GetName());

  if (SkeletalMesh == NULL && URobotPart::RobotPartAssetsBP != NULL)
  {
//    URobotPart::RobotPartAssetsBP->LoadAsset(GetSkeletalMeshAssetPtr(), FStreamableDelegate::CreateUObject(this, &URobotPart::OnSkeletalMeshLoaded));
    SkeletalMesh = URobotPart::RobotPartAssetsBP->LoadAssetSynchronous<USkeletalMesh>(GetSkeletalMeshAssetPtr());
  }

  return SkeletalMesh;
}

void URobotPart::OnSkeletalMeshLoaded()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnSkeletalMeshLoaded"), *GetName());
  SkeletalMesh = GetSkeletalMeshAssetPtr().Get();
}

UMaterial* URobotPart::GetMajorMaterial()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetMajorMaterial"), *GetName());

  if (MajorMaterial == NULL && URobotPart::RobotPartAssetsBP != NULL)
  {
//    URobotPart::RobotPartAssetsBP->LoadAsset(GetMajorMaterialAssetPtr(), FStreamableDelegate::CreateUObject(this, &URobotPart::OnMajorMaterialLoaded));
    MajorMaterial = URobotPart::RobotPartAssetsBP->LoadAssetSynchronous<UMaterial>(GetMajorMaterialAssetPtr());
  }

  return MajorMaterial;

}

void URobotPart::OnMajorMaterialLoaded()
{
  MajorMaterial = GetMajorMaterialAssetPtr().Get();
}

UManufacturer* URobotPart::GetManufacturer()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetManufacturer"), *GetName());

  if (Manufacturer == NULL && URobotPart::RobotPartAssetsBP != NULL)// && GetManufacturerAssetPtr() != NULL)
  {
//    URobotPart::RobotPartAssetsBP->LoadAsset(GetManufacturerAssetPtr(), FStreamableDelegate::CreateUObject(this, &URobotPart::OnManufacturerLoaded));
    Manufacturer = URobotPart::RobotPartAssetsBP->LoadAssetSynchronous<UManufacturer>(GetManufacturerAssetPtr());
  }

  return Manufacturer;

}

void URobotPart::OnManufacturerLoaded()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnManufacturerLoaded"), *GetName());
  Manufacturer = GetManufacturerAssetPtr().Get();
}

UTexture2D* URobotPart::GetCardIcon()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetCardIcon"), *GetName());
  if (CardIcon == NULL && URobotPart::RobotPartAssetsBP != NULL)
  {
//    URobotPart::RobotPartAssetsBP->LoadAsset(GetCardIconAssetPtr(), FStreamableDelegate::CreateUObject(this, &URobotPart::OnCardIconLoaded));
    CardIcon = URobotPart::RobotPartAssetsBP->LoadAssetSynchronous<UTexture2D>(GetCardIconAssetPtr());
  }

  return CardIcon;
}

void URobotPart::OnCardIconLoaded()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnCardIconLoaded"), *GetName());
  CardIcon = GetCardIconAssetPtr().Get(); 
}

void URobotPart::SetupAssetAttributes()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetupAssetAttributes"), *GetName());
  GetSkeletalMesh();
  GetMajorMaterial();
  GetManufacturer();
  GetCardIcon();
}

TArray<FStatText> URobotPart::GetStatsText()
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
