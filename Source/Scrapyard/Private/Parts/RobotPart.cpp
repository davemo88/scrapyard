// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPart.h"
#include "RobotPartAssets.h"
#include "Engine/SkeletalMesh.h"

URobotPartAssets* URobotPart::RobotPartAssetsBP = nullptr;

USkeletalMesh* URobotPart::GetSkeletalMesh()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetSkeletalMesh"), *GetName());

  if (SkeletalMesh == NULL && URobotPart::RobotPartAssetsBP != NULL)
  {
    URobotPart::RobotPartAssetsBP->LoadAsset(GetSkeletalMeshAssetPtr(), FStreamableDelegate::CreateUObject(this, &URobotPart::OnSkeletalMeshLoaded));
  }

  return SkeletalMesh;
}

void URobotPart::OnSkeletalMeshLoaded()
{
  SkeletalMesh = GetSkeletalMeshAssetPtr().Get();
}

UMaterial* URobotPart::GetMajorMaterial()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetMajorMaterial"), *GetName());

  if (MajorMaterial == NULL && URobotPart::RobotPartAssetsBP != NULL)
  {
    URobotPart::RobotPartAssetsBP->LoadAsset(GetMajorMaterialAssetPtr(), FStreamableDelegate::CreateUObject(this, &URobotPart::OnMajorMaterialLoaded));
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

  if (Manufacturer == NULL && URobotPart::RobotPartAssetsBP != NULL)
  {
    URobotPart::RobotPartAssetsBP->LoadAsset(GetManufacturerAssetPtr(), FStreamableDelegate::CreateUObject(this, &URobotPart::OnManufacturerLoaded));
  }

  return Manufacturer;

}

void URobotPart::OnManufacturerLoaded()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnManufacturerLoaded"), *GetName());
  Manufacturer = GetManufacturerAssetPtr().Get();
}
