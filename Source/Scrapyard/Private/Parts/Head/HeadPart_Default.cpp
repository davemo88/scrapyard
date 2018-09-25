// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadPart_Default.h"
#include "Parts/RobotPartAssets.h"

UHeadPart_Default::UHeadPart_Default()
{
  PartName = TEXT("Default Head");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;
}

USkeletalMesh* UHeadPart_Default::GetSkeletalMesh()
{
  URobotPartAssets* RobotPartAssets = GetRobotPartAssets();
  if (RobotPartAssets != NULL)
  {
    return RobotPartAssets->HeadPart_Default_SkeletalMesh;
  }
  return nullptr;
}
