// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/Material.h"
#include "Engine/Texture2D.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StreamableManager.h"
#include "UObject/NoExportTypes.h"
#include "Game/ScrapyardGameInstance.h"
#include "RobotPartAssets.generated.h"

class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class UHandheldPart;
class UScrapyardGameInstance;

/**
 * 
 */
UCLASS(Blueprintable)
class SCRAPYARD_API URobotPartAssets : public UObject
{
  GENERATED_BODY()

public:

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HeadPart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> CorePart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> ArmsPart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> LegsPart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HandheldPart_Default_SkeletalMesh;

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> RedMaterial;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> BlueMaterial;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> GreenMaterial;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> PurpleMaterial;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> OrangeMaterial;

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> HeadCardIcon;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> CoreCardIcon;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> ArmsCardIcon;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> LegsCardIcon;


//  template<typename T>
  void LoadAsset(TSoftObjectPtr<UObject> SoftObjectPtr, FStreamableDelegate DelegateToCall);

//  void LoadAsset(TSoftObjectPtr<UObject> SoftObjectPtr, FStreamableDelegate DelegateToCall);

//TODO: maybe can simplify this by just calling LoadSynchronous on the TSoftObjectPtr
//TODO: understand why template funciton bodiesin header file and not cpp file
  template<typename T>
  T* LoadAssetSynchronous(TSoftObjectPtr<UObject> SoftObjectPtr)
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::LoadAssetSynchronous"), *GetName());
  
    T* Asset = nullptr;
  
    if (!SoftObjectPtr.IsNull() && GameInstance)
    {
      UE_LOG(LogTemp, Warning, TEXT("GameInstance For LoadAsset OK"));
      TSharedPtr<FStreamableHandle> StreamableHandle = GameInstance->AssetLoader.RequestSyncLoad(SoftObjectPtr.ToSoftObjectPath());
      Asset = Cast<T>(StreamableHandle->GetLoadedAsset());
    }
  
    return Asset;
  };
//  TSharedPtr<FStreamableHandle> LoadAssetSynchronous(TSoftObjectPtr<UObject> SoftObjectPtr);

// TODO: this is hack because getting gameinstance outside of actors is mysterious
  UScrapyardGameInstance* GameInstance;
};
