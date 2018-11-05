// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadPart_Orange.h"

UHeadPart_Orange::UHeadPart_Orange()
{
  PartName = NSLOCTEXT("SY", "OrangeHeadName", "Orange Head");
  Mass = 55;
  HitPoints = 77;
  PowerDrain = 111;
  PhysicalDefense = 11;
  EnergyDefense = 11;
  TargetingAbility = 21;
  ChipSlots = 2;

}

TSoftObjectPtr<USkeletalMesh> UHeadPart_Orange::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->HeadPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UHeadPart_Orange::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->OrangeMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UHeadPart_Orange::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->OrangeCorp : nullptr;
} 






