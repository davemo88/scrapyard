// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadPart_Purple.h"
#include "RobotPartAssets.h"

const uint32 UHeadPart_Purple::PartID = 3005;

UHeadPart_Purple::UHeadPart_Purple()
{
  PartName = NSLOCTEXT("SY", "PurpleHeadName", "Purple Head");
  Manufacturer = GetManufacturer("Purple");
  Mass = 64;
  HitPoints = 41;
  PowerDrain = 100;
  PhysicalDefense = 8;
  EnergyDefense = 22;
  TargetingAbility = 22;
  ChipSlots = 2;

}

TSoftObjectPtr<USkeletalMesh> UHeadPart_Purple::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->HeadPart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UHeadPart_Purple::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->PurpleMaterial : nullptr;
} 






