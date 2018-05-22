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

	UPROPERTY(EditAnywhere)
	FString ManufacturerName;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* Logo;
};
