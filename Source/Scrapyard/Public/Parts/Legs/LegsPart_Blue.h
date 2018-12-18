// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/LegsPart.h"
#include "LegsPart_Blue.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ULegsPart_Blue : public ULegsPart
{
	GENERATED_BODY()
	
public:

  ULegsPart_Blue();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() override;
  
	
	
	
};
