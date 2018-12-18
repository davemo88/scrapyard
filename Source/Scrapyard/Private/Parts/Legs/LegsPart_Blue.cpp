// Fill out your copyright notice in the Description page of Project Settings.


#include "LegsPart_Blue.h"


ULegsPart_Blue::ULegsPart_Blue()
{
  PartName = NSLOCTEXT("SY", "BlueLegsName", "Blue Legs");
  Manufacturer = Manufacturers["Blue"];
  Mass = 101;
  HitPoints = 50;
  PowerDrain = 99;
  PhysicalDefense = 8;
  EnergyDefense = 7;
  MovementSpeed = 117;

}

TSoftObjectPtr<USkeletalMesh> ULegsPart_Blue::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->LegsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> ULegsPart_Blue::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->BlueMaterial : nullptr;
} 




