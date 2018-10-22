// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsPart_Red.h"
#include "Parts/RobotPartAssets.h"

UArmsPart_Red::UArmsPart_Red()
{
  PartName = TEXT("Red Arms");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

  Manufacturer = GetManufacturer();
  CardIcon = GetCardIcon();

}

TSoftObjectPtr<USkeletalMesh> UArmsPart_Red::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UArmsPart_Red::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->RedMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UArmsPart_Red::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->RedCorp : nullptr;
} 





