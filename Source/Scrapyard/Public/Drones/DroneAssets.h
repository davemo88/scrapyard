// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/StaticMesh.h"
#include "DroneAssets.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SCRAPYARD_API UDroneAssets : public UObject
{
  GENERATED_BODY()
  
public:

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UStaticMesh> DefaultMesh;
  
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> DefaultMaterial;

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UParticleSystem> DefaultOnDestroyParticleSystem;
  
};
