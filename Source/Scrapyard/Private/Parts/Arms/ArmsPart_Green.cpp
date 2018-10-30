// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsPart_Green.h"
#include "Parts/RobotPartAssets.h"


UArmsPart_Green::UArmsPart_Green()
{
  PartName = NSLOCTEXT("SY", "GreenArmsName", "Green Arms");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

}

TSoftObjectPtr<USkeletalMesh> UArmsPart_Green::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UArmsPart_Green::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->GreenMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UArmsPart_Green::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->GreenCorp : nullptr;
} 





