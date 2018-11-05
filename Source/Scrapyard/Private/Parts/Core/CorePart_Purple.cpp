// Fill out your copyright notice in the Description page of Project Settings.


#include "CorePart_Purple.h"


UCorePart_Purple::UCorePart_Purple()
{
  PartName = NSLOCTEXT("SY", "PurpleCoreName", "Purple Core");
  Mass = 100;
  HitPoints = 97;
  PowerDrain = 100;
  PhysicalDefense = 10;
  EnergyDefense = 10;
  PowerSupply = 1420;
  BoosterThrust = 77;
  BoosterPowerDrain = 122;

}

TSoftObjectPtr<USkeletalMesh> UCorePart_Purple::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->CorePart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UCorePart_Purple::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->PurpleMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UCorePart_Purple::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->PurpleCorp : nullptr;
} 





