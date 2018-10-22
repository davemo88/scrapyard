// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadPart_Red.h"

UHeadPart_Red::UHeadPart_Red()
{
  PartName = TEXT("Red Head");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

  Manufacturer = GetManufacturer();

}

TSoftObjectPtr<USkeletalMesh> UHeadPart_Red::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->HeadPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UHeadPart_Red::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->RedMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UHeadPart_Red::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->RedCorp : nullptr;
} 






