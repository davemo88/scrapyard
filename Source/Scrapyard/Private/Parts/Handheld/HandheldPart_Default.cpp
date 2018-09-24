// Fill out your copyright notice in the Description page of Project Settings.


#include "HandheldPart_Default.h"
#include "Parts/RobotPartAssets.h"

UHandheldPart_Default::UHandheldPart_Default()
{
  PartName = TEXT("Default Handheld");
  Mass = 100;
  PowerDrain = 100;
  BallisticDefense = 10;
  EnergyDefense = 10;
}

USkeletalMesh* UHandheldPart_Default::GetSkeletalMesh()
{
  URobotPartAssets* RobotPartAssets = GetRobotPartAssets();
  if (RobotPartAssets != NULL)
  {
    UE_LOG(LogTemp, Warning, TEXT("RobotPartAssets isn't NULL"));
    return RobotPartAssets->HandheldPart_Default_SkeletalMesh;
  }
  else 
  {
    UE_LOG(LogTemp, Warning, TEXT("RobotPartAssets is NULL"));
  }
  
  return nullptr;
}




