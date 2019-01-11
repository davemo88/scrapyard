// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsPart_Red.h"
#include "Parts/RobotPartAssets.h"

const uint32 UArmsPart_Red::PartID = 1001;

UArmsPart_Red::UArmsPart_Red()
{
  PartName = NSLOCTEXT("SY", "RedArmsName", "Red Arms");
  Manufacturer = GetManufacturer("Red");
  Mass = 79;
  HitPoints = 75;
  PowerDrain = 12;
  PhysicalDefense = 15;
  EnergyDefense = 9;
  WeaponDexterity = 5;

}

TSoftObjectPtr<USkeletalMesh> UArmsPart_Red::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UArmsPart_Red::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->RedMaterial : nullptr;
} 






