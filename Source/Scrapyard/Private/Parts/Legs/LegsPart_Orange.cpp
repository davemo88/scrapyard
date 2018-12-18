// Fill out your copyright notice in the Description page of Project Settings.


#include "LegsPart_Orange.h"



ULegsPart_Orange::ULegsPart_Orange()
{
  PartName = NSLOCTEXT("SY", "OrangeLegsName", "Orange Legs");
  Manufacturer = Manufacturers["Orange"];
  Mass = 77;
  HitPoints = 33;
  PowerDrain = 81;
  PhysicalDefense = 5;
  EnergyDefense = 5;
  MovementSpeed = 163;

}

TSoftObjectPtr<USkeletalMesh> ULegsPart_Orange::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->LegsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> ULegsPart_Orange::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->OrangeMaterial : nullptr;
} 


