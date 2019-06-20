// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "Rarity.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URarity : public UDataAsset
{
  GENERATED_BODY()
  
public:

  UPROPERTY(EditAnywhere)
  FString RarityName;

  UPROPERTY(EditAnywhere)
  UTexture2D* RaritySymbol;
};
