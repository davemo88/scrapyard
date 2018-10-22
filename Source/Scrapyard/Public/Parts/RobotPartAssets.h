// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/StreamableManager.h"
#include "RobotPartAssets.generated.h"

class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class UHandheldPart;
class UManufacturer;
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
  TSoftObjectPtr<UManufacturer> RedCorp;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UManufacturer> BlueCorp;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UManufacturer> GreenCorp;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UManufacturer> OrangeCorp;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UManufacturer> PurpleCorp;

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

// TODO: this is hack because getting gameinstance outside of actors is mysterious
  UScrapyardGameInstance* GameInstance;
};
