// Fill out your copyright notice in the Description page of Project Settings.


#include "LegsPart_Green.h"


ULegsPart_Green::ULegsPart_Green()
{
  PartName = NSLOCTEXT("SY", "GreenLegsName", "Green Legs");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;
  MovementSpeed = 10;

}

TSoftObjectPtr<USkeletalMesh> ULegsPart_Green::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->LegsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> ULegsPart_Green::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->GreenMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> ULegsPart_Green::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->GreenCorp : nullptr;
} 



