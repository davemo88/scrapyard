// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/HeadPart.h"
#include "HeadPart_Purple.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UHeadPart_Purple : public UHeadPart
{
  GENERATED_BODY()
  
public:
  static const uint32 PartID; 

  UHeadPart_Purple();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() override;
  
  
  
  
};
