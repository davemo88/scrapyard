// Fill out your copyright notice in the Description page of Project Settings.


#include "LegsPart_Default.h"
#include "Parts/RobotPartAssets.h"

ULegsPart_Default::ULegsPart_Default()
{
  PartName = TEXT("Default Legs");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;

  SkeletalMesh = GetSkeletalMesh();
  
}

USkeletalMesh* ULegsPart_Default::GetSkeletalMesh()
{
  URobotPartAssets* RobotPartAssets = GetRobotPartAssets();
  if (RobotPartAssets != NULL)
  {
    UE_LOG(LogTemp, Warning, TEXT("RobotPartAssets isn't NULL"));
    return RobotPartAssets->LegsPart_Default_SkeletalMesh;
  }
  else 
  {
    UE_LOG(LogTemp, Warning, TEXT("RobotPartAssets is NULL"));
  }
  
  return nullptr;
}




