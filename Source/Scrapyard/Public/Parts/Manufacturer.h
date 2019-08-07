// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Manufacturer.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UManufacturer : public UObject
{
  GENERATED_BODY()

public:

  UPROPERTY()
  FText ManufacturerName;
  UPROPERTY()
  UTexture2D* Card;
  UPROPERTY()
  UTexture2D* MiniCard;

};
