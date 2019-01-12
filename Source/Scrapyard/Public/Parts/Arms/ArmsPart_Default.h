// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/ArmsPart.h"
#include "ArmsPart_Default.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UArmsPart_Default : public UArmsPart
{
  GENERATED_BODY()

public:

  static const uint32 PartID; 
  
  virtual uint32 GetPartID()
  {
    return PartID;
  };

  UArmsPart_Default();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;

};
