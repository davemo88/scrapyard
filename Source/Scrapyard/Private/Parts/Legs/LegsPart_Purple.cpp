// Fill out your copyright notice in the Description page of Project Settings.


#include "LegsPart_Purple.h"
#include "RobotPartAssets.h"

const uint32 ULegsPart_Purple::PartID = 4005;

ULegsPart_Purple::ULegsPart_Purple()
{
  PartName = NSLOCTEXT("SY", "PurpleLegsName", "Purple Legs");
  Manufacturer = GetManufacturer("Purple");
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



