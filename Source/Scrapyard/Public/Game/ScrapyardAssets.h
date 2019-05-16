// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UI/UIAssets.h"
#include "Parts/PartAssets.h"
#include "ScrapyardAssets.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class SCRAPYARD_API UScrapyardAssets : public UObject
{
  GENERATED_BODY()
  
public:

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<UUIAssets> UIAssetsBPClass;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<UPartAssets> PartAssetsBPClass;

  UUIAssets* UIAssetsBP;

  UPartAssets* PartAssetsBP;

};
