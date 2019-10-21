// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Particles/ParticleSystem.h"
#include "ProjectileAssets.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SCRAPYARD_API UProjectileAssets : public UObject
{
  GENERATED_BODY()
  
public:

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UParticleSystem> LaserBeamParticleSystem;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UStaticMesh> BazookaProjectileMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> BazookaProjectileMaterial;
  
};
