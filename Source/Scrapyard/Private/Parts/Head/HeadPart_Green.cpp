// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadPart_Green.h"

UHeadPart_Green::UHeadPart_Green()
{
  PartName = TEXT("Green Head");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

}

TSoftObjectPtr<USkeletalMesh> UHeadPart_Green::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->HeadPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UHeadPart_Green::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->GreenMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UHeadPart_Green::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->GreenCorp : nullptr;
} 





