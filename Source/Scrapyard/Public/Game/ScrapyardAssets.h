// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScrapyardAssets.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SCRAPYARD_API UScrapyardAssets : public UObject
{
  GENERATED_BODY()
  
public:

  UUIAssets* UIAssetsBP;

  UPartAssets* PartAssetsBP;

};
