// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadPart_Green.h"
#include "RobotPartAssets.h"

const uint32 UHeadPart_Green::PartID = 3003;

UHeadPart_Green::UHeadPart_Green()
{
  PartName = NSLOCTEXT("SY", "GreenHeadName", "Green Head");
  Manufacturer = GetManufacturer("Green");
  Mass = 100;
  HitPoints = 69;
  PowerDrain = 50;
  PhysicalDefense = 7;
  EnergyDefense = 14;
  TargetingAbility = 8;
  ChipSlots = 2; 

}

TSoftObjectPtr<USkeletalMesh> UHeadPart_Green::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->HeadPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UHeadPart_Green::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->GreenMaterial : nullptr;
} 





