// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/ScrapyardProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "LaserProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ALaserProjectile : public AScrapyardProjectile
{
  GENERATED_BODY()
  
public:

  ALaserProjectile();
  
  UParticleSystemComponent* LaserBeam;
};
