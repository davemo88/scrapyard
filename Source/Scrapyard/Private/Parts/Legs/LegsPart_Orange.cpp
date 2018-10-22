// Fill out your copyright notice in the Description page of Project Settings.


#include "LegsPart_Orange.h"



ULegsPart_Orange::ULegsPart_Orange()
{
  PartName = TEXT("Orange Legs");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

  Manufacturer = GetManufacturer();

}

TSoftObjectPtr<USkeletalMesh> ULegsPart_Orange::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->LegsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> ULegsPart_Orange::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->OrangeMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> ULegsPart_Orange::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->OrangeCorp : nullptr;
} 


