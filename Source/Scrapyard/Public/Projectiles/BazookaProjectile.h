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

  UPROPERTY()
  FVector FireDirection;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UPROPERTY(EditAnywhere)
  UStaticMeshComponent* StaticMeshComponent;

  float ProjectileSpeed;

  UPROPERTY(EditAnywhere)
  UParticleSystem* OnDestroyParticleSystem;

public:	
  // Called every frame
  virtual void Tick(float DeltaTime) override;
	
  virtual void LifeSpanExpired() override;
	
  virtual void BeginDestroy() override;

};
