// Fill out your copyright notice in the Description page of Project Settings.


#include "CorePart_Blue.h"
#include "RobotPartAssets.h"

const uint32 UCorePart_Blue::PartID = 2002;

UCorePart_Blue::UCorePart_Blue()
{
  PartName = NSLOCTEXT("SY", "BlueCoreName", "Blue Core");
  Manufacturer = GetManufacturer("Blue");
  Mass = 100;
  HitPoints = 155;
  PowerDrain = 100;
  PhysicalDefense = 10;
  EnergyDefense = 10;
  PowerSupply = 1022;
  BoosterThrust = 80;
  BoosterPowerDrain = 107;

}

TSoftObjectPtr<USkeletalMesh> UCorePart_Blue::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->CorePart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UCorePart_Blue::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->BlueMaterial : nullptr;
} 


