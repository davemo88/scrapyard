// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/HeadPart.h"
#include "HeadPart_Green.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UHeadPart_Green : public UHeadPart
{
  GENERATED_BODY()
  
public:

  UHeadPart_Green();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() override;
  
  
  
};
