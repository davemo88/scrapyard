// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadPart_Purple.h"

UHeadPart_Purple::UHeadPart_Purple()
{
  PartName = NSLOCTEXT("SY", "PurpleHeadName", "Purple Head");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

}

TSoftObjectPtr<USkeletalMesh> UHeadPart_Purple::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->HeadPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UHeadPart_Purple::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->PurpleMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UHeadPart_Purple::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->PurpleCorp : nullptr;
} 






