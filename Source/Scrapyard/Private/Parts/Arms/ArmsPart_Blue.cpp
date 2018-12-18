// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsPart_Blue.h"

UArmsPart_Blue::UArmsPart_Blue()
{
  PartName = NSLOCTEXT("SY", "BlueArmsName", "Blue Arms");
  Manufacturer = Manufacturers["Blue"];
  Mass = 56;
  HitPoints = 44;
  PowerDrain = 18;
  PhysicalDefense = 17;
  EnergyDefense = 15;
  WeaponDexterity = 7;
}

TSoftObjectPtr<USkeletalMesh> UArmsPart_Blue::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UArmsPart_Blue::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->BlueMaterial : nullptr;
} 
