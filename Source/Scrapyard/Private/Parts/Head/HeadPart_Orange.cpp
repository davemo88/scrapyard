// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadPart_Orange.h"

UHeadPart_Orange::UHeadPart_Orange()
{
  PartName = TEXT("Orange Head");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

}

TSoftObjectPtr<USkeletalMesh> UHeadPart_Orange::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->HeadPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UHeadPart_Orange::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->OrangeMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UHeadPart_Orange::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->OrangeCorp : nullptr;
} 






