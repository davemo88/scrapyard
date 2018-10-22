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

  ULegsPart_Green();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() override;
  TSoftObjectPtr<UManufacturer> GetManufacturerAssetPtr() override;
  
	
	
	
};
