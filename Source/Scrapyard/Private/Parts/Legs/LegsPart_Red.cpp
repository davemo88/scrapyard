// Fill out your copyright notice in the Description page of Project Settings.


#include "LegsPart_Red.h"


ULegsPart_Red::ULegsPart_Red()
{
  PartName = TEXT("Red Legs");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

}

TSoftObjectPtr<USkeletalMesh> ULegsPart_Red::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->LegsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> ULegsPart_Red::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->RedMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> ULegsPart_Red::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->RedCorp : nullptr;
} 



