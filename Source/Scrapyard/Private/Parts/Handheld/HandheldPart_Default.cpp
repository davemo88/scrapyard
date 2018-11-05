// Fill out your copyright notice in the Description page of Project Settings.


#include "HandheldPart_Default.h"
#include "Parts/RobotPartAssets.h"

UHandheldPart_Default::UHandheldPart_Default()
{
  PartName = NSLOCTEXT("SY", "DefaultHandheldName", "Default Handheld");
  Mass = 100;
  PowerDrain = 100;
  PhysicalDefense = 10;
  EnergyDefense = 10;
}

TSoftObjectPtr<USkeletalMesh> UHandheldPart_Default::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->HandheldPart_Default_SkeletalMesh : nullptr;
}




