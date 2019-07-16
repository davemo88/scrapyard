// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardAssets.h"
#include "Scrapyard.h"

void UScrapyardAssets::InitAssetsBP()
{
  if (UIAssetsBPClass != nullptr)
  {
    UE_LOG(LogAssets, Verbose, TEXT("Loading UIAssetsBP"), *GetName());
    UIAssetsBP = UIAssetsBPClass->GetDefaultObject<UUIAssets>();
  }
  if (PartAssetsBPClass != nullptr)
  {
    UE_LOG(LogAssets, Verbose, TEXT("Loading PartAssetsBP"), *GetName());
    PartAssetsBP = PartAssetsBPClass->GetDefaultObject<UPartAssets>();
  }
  if (DroneAssetsBPClass != nullptr)
  {
    UE_LOG(LogAssets, Verbose, TEXT("Loading DroneAssetsBP"), *GetName());
    DroneAssetsBP = DroneAssetsBPClass->GetDefaultObject<UDroneAssets>();
  }
  if (ProjectileAssetsBPClass != nullptr)
  {
    UE_LOG(LogAssets, Verbose, TEXT("Loading ProjectileAssetsBP"), *GetName());
    ProjectileAssetsBP = ProjectileAssetsBPClass->GetDefaultObject<UProjectileAssets>();
  }
}
