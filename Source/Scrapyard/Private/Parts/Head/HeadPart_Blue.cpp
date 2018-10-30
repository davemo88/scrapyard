// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadPart_Blue.h"

UHeadPart_Blue::UHeadPart_Blue()
{
  PartName = NSLOCTEXT("SY", "BlueHeadName", "Blue Head");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

}

TSoftObjectPtr<USkeletalMesh> UHeadPart_Blue::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->HeadPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UHeadPart_Blue::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->BlueMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UHeadPart_Blue::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->BlueCorp : nullptr;
} 



