// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsPart_Purple.h"
#include "Parts/RobotPartAssets.h"

UArmsPart_Purple::UArmsPart_Purple()
{
  PartName = TEXT("Purple Arms");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

}

TSoftObjectPtr<USkeletalMesh> UArmsPart_Purple::GetSkeletalMeshAssetPtr()
{
  return (RobotPartAssetsBP != NULL) ? RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh : nullptr;
}






