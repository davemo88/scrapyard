// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/CorePart.h"
#include "CorePart_Orange.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UCorePart_Orange : public UCorePart
{
  GENERATED_BODY()
  
  
public:

  UCorePart_Orange();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() override;
  TSoftObjectPtr<UManufacturer> GetManufacturerAssetPtr() override;
  
  
  
};
