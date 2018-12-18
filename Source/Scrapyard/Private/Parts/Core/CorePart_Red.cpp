// Fill out your copyright notice in the Description page of Project Settings.


#include "CorePart_Red.h"


UCorePart_Red::UCorePart_Red()
{
  PartName = NSLOCTEXT("SY", "RedCoreName", "Red Core");
  Manufacturer = Manufacturers["Red"];
  Mass = 100;
  HitPoints = 211;
  PowerDrain = 100;
  PhysicalDefense = 10;
  EnergyDefense = 10;
  PowerSupply = 704;
  BoosterThrust = 80;
  BoosterPowerDrain = 130;

}

TSoftObjectPtr<USkeletalMesh> UCorePart_Red::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->CorePart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UCorePart_Red::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->RedMaterial : nullptr;
} 

