// Fill out your copyright notice in the Description page of Project Settings.


#include "LegsPart_Purple.h"


ULegsPart_Purple::ULegsPart_Purple()
{
  PartName = NSLOCTEXT("SY", "PurpleLegsName", "Purple Legs");
  Manufacturer = Manufacturers["Purple"];
  Mass = 68;
  HitPoints = 30;
  PowerDrain = 100;
  PhysicalDefense = 2;
  EnergyDefense = 10;
  MovementSpeed = 133;

}

TSoftObjectPtr<USkeletalMesh> ULegsPart_Purple::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->LegsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> ULegsPart_Purple::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->PurpleMaterial : nullptr;
} 



