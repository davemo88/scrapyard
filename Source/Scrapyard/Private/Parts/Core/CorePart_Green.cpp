// Fill out your copyright notice in the Description page of Project Settings.


#include "CorePart_Green.h"

UCorePart_Green::UCorePart_Green()
{
  PartName = NSLOCTEXT("SY", "GreenCoreName", "Green Core");
  Mass = 100;
  HitPoints = 188;
  PowerDrain = 100;
  PhysicalDefense = 10;
  EnergyDefense = 10;
  PowerSupply = 888;
  BoosterThrust = 55;
  BoosterPowerDrain = 55;

}

TSoftObjectPtr<USkeletalMesh> UCorePart_Green::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->CorePart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UCorePart_Green::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->GreenMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UCorePart_Green::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->GreenCorp : nullptr;
} 





