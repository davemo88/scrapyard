// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "Manufacturer.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UManufacturer : public UDataAsset
{
  GENERATED_BODY()

public:

  UPROPERTY(EditDefaultsOnly)
  FString ManufacturerName;
  
  UPROPERTY(EditDefaultsOnly)
  UTexture2D* Logo;

  UPROPERTY(EditDefaultsOnly)
  FLinearColor CardBackgroundColor;
};
