// Fill out your copyright notice in the Description page of Project Settings.


#include "LegsPart_Red.h"
#include "RobotPartAssets.h"


ULegsPart_Red::ULegsPart_Red()
{
  PartName = NSLOCTEXT("SY", "RegLegsName", "Red Legs");
  Manufacturer = GetManufacturer("Red");
  Mass = 121;
  HitPoints = 86;
  PowerDrain = 101;
  PhysicalDefense = 15;
  EnergyDefense = 3;
  MovementSpeed = 77;

}

TSoftObjectPtr<USkeletalMesh> ULegsPart_Red::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->LegsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> ULegsPart_Red::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->RedMaterial : nullptr;
} 




