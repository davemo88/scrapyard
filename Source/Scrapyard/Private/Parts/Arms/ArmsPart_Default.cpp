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

USkeletalMesh* UArmsPart_Default::GetSkeletalMesh()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetSkeletalMesh"), *GetName());
  URobotPartAssets* RobotPartAssets = GetRobotPartAssets();
  if (RobotPartAssets != NULL)
  {
    UE_LOG(LogTemp, Warning, TEXT("RobotPartAssets isn't NULL"));
    return RobotPartAssets->ArmsPart_Default_SkeletalMesh;
  }
  else 
  {
    UE_LOG(LogTemp, Warning, TEXT("RobotPartAssets is NULL"));
  }
  
  return nullptr;
}
