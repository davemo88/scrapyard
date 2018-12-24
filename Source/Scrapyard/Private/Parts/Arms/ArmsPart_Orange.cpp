// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsPart_Orange.h"
#include "Parts/RobotPartAssets.h"

UArmsPart_Orange::UArmsPart_Orange()
{
  PartName = NSLOCTEXT("SY", "OrangeArmsName", "Orange Arms");
  Manufacturer = GetManufacturer("Orange");
  Mass = 52;
  HitPoints = 42;
  PowerDrain = 12;
  PhysicalDefense = 12;
  EnergyDefense = 11;
  WeaponDexterity = 20;

}

TSoftObjectPtr<USkeletalMesh> UArmsPart_Orange::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UArmsPart_Orange::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->OrangeMaterial : nullptr;
} 






