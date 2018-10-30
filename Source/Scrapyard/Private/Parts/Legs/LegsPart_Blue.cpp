// Fill out your copyright notice in the Description page of Project Settings.


#include "LegsPart_Blue.h"


ULegsPart_Blue::ULegsPart_Blue()
{
  PartName = NSLOCTEXT("SY", "BlueLegsName", "Blue Legs");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;
  MovementSpeed = 10;

}

TSoftObjectPtr<USkeletalMesh> ULegsPart_Blue::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->LegsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> ULegsPart_Blue::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->BlueMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> ULegsPart_Blue::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->BlueCorp : nullptr;
} 




