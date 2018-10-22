// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsPart_Purple.h"
#include "Parts/RobotPartAssets.h"

UArmsPart_Purple::UArmsPart_Purple()
{
  PartName = TEXT("Purple Arms");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

  Manufacturer = GetManufacturer();
  CardIcon = GetCardIcon();

}

TSoftObjectPtr<USkeletalMesh> UArmsPart_Purple::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UArmsPart_Purple::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->PurpleMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UArmsPart_Purple::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->PurpleCorp : nullptr;
} 





