// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/LegsPart.h"
#include "LegsPart_Green.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ULegsPart_Green : public ULegsPart
{
	GENERATED_BODY()
	
public:
  static const uint32 PartID; 
  
  virtual uint32 GetPartID()
  {
    return PartID;
  };

  ULegsPart_Green();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() override;
  
	
	
	
};
