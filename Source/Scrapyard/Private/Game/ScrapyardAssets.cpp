// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardAssets.h"

void UScrapyardAssets::InitAssetsBP()
{
  if (UIAssetsBPClass != nullptr)
  {
    UE_LOG(LogTemp, Warning, TEXT("Loading UIAssetsBP"), *GetName());
    UIAssetsBP = UIAssetsBPClass->GetDefaultObject<UUIAssets>();
  }
  if (PartAssetsBPClass != nullptr)
  {
    UE_LOG(LogTemp, Warning, TEXT("Loading PartAssetsBP"), *GetName());
    PartAssetsBP = PartAssetsBPClass->GetDefaultObject<UPartAssets>();
  }
  if (DroneAssetsBPClass != nullptr)
  {
    UE_LOG(LogTemp, Warning, TEXT("Loading DroneAssetsBP"), *GetName());
    DroneAssetsBP = DroneAssetsBPClass->GetDefaultObject<UDroneAssets>();
  }
}
