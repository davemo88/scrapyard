// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/ArmsPart.h"
#include "ArmsPart_Green.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UArmsPart_Green : public UArmsPart
{
  GENERATED_BODY()
  
public:

  UArmsPart_Green();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() override;
  TSoftObjectPtr<UManufacturer> GetManufacturerAssetPtr() override;
  
};
