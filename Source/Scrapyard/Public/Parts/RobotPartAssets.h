// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RobotPartAssets.generated.h"

class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class UHandheldPart;

/**
 * 
 */
UCLASS(Blueprintable)
class SCRAPYARD_API URobotPartAssets : public UObject
{
  GENERATED_BODY()

public:

  UPROPERTY(EditDefaultsOnly)
  TAssetPtr<USkeletalMesh> HeadPart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TAssetPtr<USkeletalMesh> CorePart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TAssetPtr<USkeletalMesh> ArmsPart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TAssetPtr<USkeletalMesh> LegsPart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TAssetPtr<USkeletalMesh> HandheldPart_Default_SkeletalMesh;

  UPROPERTY(EditDefaultsOnly)
  TAssetPtr<UMaterial> RedMaterial;
  UPROPERTY(EditDefaultsOnly)
  TAssetPtr<UMaterial> BlueMaterial;
  UPROPERTY(EditDefaultsOnly)
  TAssetPtr<UMaterial> GreenMaterial;
  UPROPERTY(EditDefaultsOnly)
  TAssetPtr<UMaterial> PurpleMaterial;
  UPROPERTY(EditDefaultsOnly)
  TAssetPtr<UMaterial> OrangeMaterial;

};
