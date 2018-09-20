// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPart.h"
#include "Parts/RobotPartAssets.h"

URobotPartAssets* URobotPart::GetRobotPartAssets()
{
  UWorld* World = GetWorld();
  if (World)
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(World->GetGameInstance());
    return GameInstance->RobotPartAssetsBP;
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("World was null for GetRobotPartAssets"));
  }
  return nullptr;
}

