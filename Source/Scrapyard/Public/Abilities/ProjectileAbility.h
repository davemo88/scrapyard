// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/ScrapyardAbility.h"
#include "ProjectileAbility.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AProjectileAbility : public AScrapyardAbility
{
  GENERATED_BODY()
  
public:

  AProjectileAbility();

  virtual void FireShot() override; 
  
protected:

  virtual void SetupTargetingProfile() override;

  virtual void ShowAbilityEffects(FAbilityEffectParams AbilityEffectParams) override;
  
  
};
