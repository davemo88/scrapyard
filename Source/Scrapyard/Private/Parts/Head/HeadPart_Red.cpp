// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadPart_Red.h"

UHeadPart_Red::UHeadPart_Red()
{
  PartName = NSLOCTEXT("SY", "RedHeadName", "Red Head");
  Mass = 111;
  HitPoints = 88;
  PowerDrain = 120;
  PhysicalDefense = 30;
  EnergyDefense = 5;
  TargetingAbility = 10;
  ChipSlots = 0;

}

TSoftObjectPtr<USkeletalMesh> UHeadPart_Red::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->HeadPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UHeadPart_Red::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->RedMaterial : nullptr;
} 

TSoftObjectPtr<UManufacturer> UHeadPart_Red::GetManufacturerAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->RedCorp : nullptr;
} 






