// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/CorePart.h"
#include "CorePart_Default.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UCorePart_Default : public UCorePart
{
  GENERATED_BODY()

  UCorePart_Default();

  USkeletalMesh* GetSkeletalMesh() override;

};
