// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPart.h"
#include "RobotPartAssets.h"
#include "Engine/SkeletalMesh.h"

URobotPartAssets* URobotPart::RobotPartAssetsBP = nullptr;

URobotPart::URobotPart()
{
//  GetManufacturer();
}

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

  if (Manufacturer == NULL && URobotPart::RobotPartAssetsBP != NULL)// && GetManufacturerAssetPtr() != NULL)
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

UTexture2D* URobotPart::GetCardIcon()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetCardIcon"), *GetName());
  if (CardIcon == NULL && URobotPart::RobotPartAssetsBP != NULL)
  {
    URobotPart::RobotPartAssetsBP->LoadAsset(GetCardIconAssetPtr(), FStreamableDelegate::CreateUObject(this, &URobotPart::OnCardIconLoaded));
  }

  return CardIcon;
}

void URobotPart::OnCardIconLoaded()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnCardIconLoaded"), *GetName());
  CardIcon = GetCardIconAssetPtr().Get(); 
}
