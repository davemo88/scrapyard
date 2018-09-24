// Fill out your copyright notice in the Description page of Project Settings.


#include "CorePart_Default.h"
#include "Parts/RobotPartAssets.h"

UCorePart_Default::UCorePart_Default()
{
  PartName = TEXT("Default Core");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;
}

USkeletalMesh* UCorePart_Default::GetSkeletalMesh()
{
  URobotPartAssets* RobotPartAssets = GetRobotPartAssets();
  if (RobotPartAssets != NULL)
  {
    UE_LOG(LogTemp, Warning, TEXT("RobotPartAssets isn't NULL"));
    return RobotPartAssets->CorePart_Default_SkeletalMesh;
  }
  else 
  {
    UE_LOG(LogTemp, Warning, TEXT("RobotPartAssets is NULL"));
  }
  
  return nullptr;
}


