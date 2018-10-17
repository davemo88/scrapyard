// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsPart_Orange.h"
#include "Parts/RobotPartAssets.h"

UArmsPart_Orange::UArmsPart_Orange()
{
  PartName = TEXT("Orange Arms");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

}

TSoftObjectPtr<USkeletalMesh> UArmsPart_Orange::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh : nullptr;
}






