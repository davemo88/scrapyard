// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsPart_Purple.h"
#include "Parts/RobotPartAssets.h"

UArmsPart_Purple::UArmsPart_Purple()
{
  PartName = NSLOCTEXT("SY", "PurpleArmsName", "Purple Arms");
  Manufacturer = GetManufacturer("Purple");
  Mass = 39;
  HitPoints = 31;
  PowerDrain = 30;
  PhysicalDefense = 3;
  EnergyDefense = 24;
  WeaponDexterity = 19;

}

TSoftObjectPtr<USkeletalMesh> UArmsPart_Purple::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UArmsPart_Purple::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->PurpleMaterial : nullptr;
} 






