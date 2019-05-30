// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UI/UIAssets.h"
#include "Parts/PartAssets.h"
#include "Drones/DroneAssets.h"
#include "ScrapyardAssets.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class SCRAPYARD_API UScrapyardAssets : public UObject
{
  GENERATED_BODY()
  
public:

  void InitAssetsBP();

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<UUIAssets> UIAssetsBPClass;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<UPartAssets> PartAssetsBPClass;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<UDroneAssets> DroneAssetsBPClass;

  UUIAssets* UIAssetsBP;

  UPartAssets* PartAssetsBP;

  UDroneAssets* DroneAssetsBP;

  template <class T>
  T* GetAsset(TSoftObjectPtr<T> AssetRef)
  {
    if (AssetRef.IsValid())
    {
      return AssetRef.Get();
    }
    else if (AssetRef.IsPending())
    {
      return AssetRef.LoadSynchronous();
    }
    return nullptr;
  }

};
