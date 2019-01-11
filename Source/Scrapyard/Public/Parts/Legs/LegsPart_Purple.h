// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/LegsPart.h"
#include "LegsPart_Purple.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ULegsPart_Purple : public ULegsPart
{
	GENERATED_BODY()
	
public:
  static const uint32 PartID; 

  ULegsPart_Purple();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() override;
  
	
	
	
};
