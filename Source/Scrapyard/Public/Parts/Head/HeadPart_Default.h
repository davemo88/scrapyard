// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/HeadPart.h"
#include "HeadPart_Default.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UHeadPart_Default : public UHeadPart
{
  GENERATED_BODY()

public:

  UHeadPart_Default();

  USkeletalMesh* GetSkeletalMesh() override;
	
};
