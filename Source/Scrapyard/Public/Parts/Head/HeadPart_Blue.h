// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/HeadPart.h"
#include "HeadPart_Blue.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UHeadPart_Blue : public UHeadPart
{
  GENERATED_BODY()
  
public:
  static const uint32 PartID; 
  
  virtual uint32 GetPartID()
  {
    return PartID;
  };

  UHeadPart_Blue();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() override;
  
};
