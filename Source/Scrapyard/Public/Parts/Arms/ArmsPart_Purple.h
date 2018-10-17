// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/ArmsPart.h"
#include "ArmsPart_Purple.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UArmsPart_Purple : public UArmsPart
{
  GENERATED_BODY()
  
public:

  UArmsPart_Purple();

  TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() override;
  
};
