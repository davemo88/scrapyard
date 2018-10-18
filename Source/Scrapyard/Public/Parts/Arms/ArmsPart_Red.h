// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/ArmsPart.h"
#include "ArmsPart_Red.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UArmsPart_Red : public UArmsPart
{
  GENERATED_BODY()
  
public:

  UArmsPart_Red();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() override;
  TSoftObjectPtr<UManufacturer> GetManufacturerAssetPtr() override;
  
};
