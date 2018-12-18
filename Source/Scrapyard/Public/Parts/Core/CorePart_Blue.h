// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/CorePart.h"
#include "CorePart_Blue.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UCorePart_Blue : public UCorePart
{
	GENERATED_BODY()
	
public:

  UCorePart_Blue();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() override;
  
	
	
	
};
