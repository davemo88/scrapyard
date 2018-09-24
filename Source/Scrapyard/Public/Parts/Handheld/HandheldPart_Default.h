// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/HandheldPart.h"
#include "HandheldPart_Default.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UHandheldPart_Default : public UHandheldPart
{
  GENERATED_BODY()

  UHandheldPart_Default();

  USkeletalMesh* GetSkeletalMesh() override;
};
