// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsPart_Default.h"
#include "Parts/RobotPartAssets.h"

UArmsPart_Default::UArmsPart_Default()
{
  PartName = TEXT("Default Arms");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

}

TSoftObjectPtr<USkeletalMesh> UArmsPart_Default::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh : nullptr;
}


