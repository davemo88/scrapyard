// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/CorePart.h"
#include "CorePart_Green.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UCorePart_Green : public UCorePart
{
  GENERATED_BODY()
  
  
public:
  static const uint32 PartID; 

  UCorePart_Green();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() override;
  
  
  
};
