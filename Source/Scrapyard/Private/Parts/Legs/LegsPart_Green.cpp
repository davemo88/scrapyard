// Fill out your copyright notice in the Description page of Project Settings.


#include "LegsPart_Green.h"


ULegsPart_Green::ULegsPart_Green()
{
  PartName = NSLOCTEXT("SY", "GreenLegsName", "Green Legs");
  Manufacturer = Manufacturers["Green"];
  Mass = 120;
  HitPoints = 67;
  PowerDrain = 77;
  PhysicalDefense = 6;
  EnergyDefense = 11;
  MovementSpeed = 93;

}

TSoftObjectPtr<USkeletalMesh> ULegsPart_Green::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->LegsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> ULegsPart_Green::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->GreenMaterial : nullptr;
} 



