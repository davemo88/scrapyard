// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadPart_Default.h"
#include "Parts/RobotPartAssets.h"

UHeadPart_Default::UHeadPart_Default()
{
  PartName = NSLOCTEXT("SY", "DefaultHeadName", "Default Head");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;
}

TSoftObjectPtr<USkeletalMesh> UHeadPart_Default::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->HeadPart_Default_SkeletalMesh : nullptr;
}
