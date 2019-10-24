// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/ScrapyardProjectile.h"
#include "BazookaProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ABazookaProjectile : public AScrapyardProjectile
{
  GENERATED_BODY()
	
public:	

  ABazookaProjectile();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UPROPERTY(EditAnywhere)
  UStaticMeshComponent* StaticMeshComponent;

  UPROPERTY(EditAnywhere)
  UParticleSystem* OnDestroyParticleSystem;

protected:

  virtual void PlayOnDestroyEffects() override;
};
