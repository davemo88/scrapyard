// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsPart_Blue.h"

UArmsPart_Blue::UArmsPart_Blue()
{
  PartName = TEXT("Blue Arms");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

  Manufacturer = GetManufacturer();
  CardIcon = GetCardIcon();

}

TSoftObjectPtr<USkeletalMesh> UArmsPart_Blue::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UArmsPart_Blue::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->BlueMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UArmsPart_Blue::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->BlueCorp : nullptr;
} 
