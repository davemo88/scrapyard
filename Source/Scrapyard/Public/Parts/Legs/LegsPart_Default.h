// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/LegsPart.h"
#include "LegsPart_Default.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ULegsPart_Default : public ULegsPart
{
  GENERATED_BODY()

public:

  ULegsPart_Default();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
};
