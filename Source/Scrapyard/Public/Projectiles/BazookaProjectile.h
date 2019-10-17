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

  FVector FireDirection;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UStaticMeshComponent* StaticMesh;

public:	
  // Called every frame
  virtual void Tick(float DeltaTime) override;
	
};
