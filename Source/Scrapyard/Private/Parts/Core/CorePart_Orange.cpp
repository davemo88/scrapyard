// Fill out your copyright notice in the Description page of Project Settings.


#include "CorePart_Orange.h"

UCorePart_Orange::UCorePart_Orange()
{
  PartName = NSLOCTEXT("SY", "OrangeCoreName", "Orange Core");
  Manufacturer = Manufacturers["Orange"];
  Mass = 100;
  HitPoints = 121;
  PowerDrain = 100;
  PhysicalDefense = 10;
  EnergyDefense = 10;
  PowerSupply = 999;
  BoosterThrust = 91;
  BoosterPowerDrain = 110;

}

TSoftObjectPtr<USkeletalMesh> UCorePart_Orange::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->CorePart_Default_SkeletalMesh : nullptr;
}

TSoftObjectPtr<UMaterial> UCorePart_Orange::GetMajorMaterialAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->OrangeMaterial : nullptr;
} 





