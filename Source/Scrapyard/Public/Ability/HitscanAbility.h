// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/ScrapyardAbility.h"
#include "HitscanAbility.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UHitscanAbility : public UScrapyardAbility
{
  GENERATED_BODY()

  UHitscanAbility();

  void FireShot() override;
	
};
