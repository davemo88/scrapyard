// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsPart_Green.h"
#include "Parts/RobotPartAssets.h"


UArmsPart_Green::UArmsPart_Green()
{
  PartName = NSLOCTEXT("SY", "GreenArmsName", "Green Arms");
  Manufacturer = Manufacturers["Green"];
  Mass = 61;
  HitPoints = 58;
  PowerDrain = 7;
  PhysicalDefense = 9;
  EnergyDefense = 16;
  WeaponDexterity = 6;

}

TSoftObjectPtr<USkeletalMesh> UArmsPart_Green::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UArmsPart_Green::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->GreenMaterial : nullptr;
} 





