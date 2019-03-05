// Fill out your copyright notice in the Description page of Project Settings.


#include "CorePart_Default.h"
#include "Parts/RobotPartAssets.h"

const uint32 UCorePart_Default::PartID = 2000;

UCorePart_Default::UCorePart_Default()
{
  PartName = NSLOCTEXT("SY", "DefaultCoreName", "Default Core");
  Mass = 100;
  HitPoints = 100;
  PowerSupply = 500;
  BoosterPowerDrain = 10;
  PhysicalDefense = 10;
  EnergyDefense = 10;
}

TSoftObjectPtr<USkeletalMesh> UCorePart_Default::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->CorePart_Default_SkeletalMesh : nullptr;
}
