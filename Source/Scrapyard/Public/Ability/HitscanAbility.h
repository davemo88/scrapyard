// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/ScrapyardAbility.h"
#include "HitscanAbility.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AHitscanAbility : public AScrapyardAbility
{
  GENERATED_BODY()

  AHitscanAbility();

  void FireShot() override;

  virtual void FireInstantHit(bool bDealDamage = true, FHitResult* OutHit = NULL) override;
	
};
