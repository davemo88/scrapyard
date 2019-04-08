// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/ScrapyardAbility.h"
#include "HitscanAbility.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AHitscanAbility : public AScrapyardAbility
{
  GENERATED_BODY()

public:

  AHitscanAbility();

  uint32 AbilityRange;

  virtual void BeginPlay() override;
  virtual void Tick(float DeltaTime) override;

  void FireShot() override;

  virtual void FireInstantHit(bool bDealDamage = true, FHitResult* OutHit = NULL) override;
	
};
