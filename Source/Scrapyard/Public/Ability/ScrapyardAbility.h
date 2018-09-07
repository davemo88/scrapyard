// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScrapyardAbility.generated.h"

class AbilityState;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UScrapyardAbility : public UObject
{
  GENERATED_BODY()

  UFUNCTION()
  virtual void StartFire(uint8 FireModeNum);
  UFUNCTION()
  virtual void StopFire(uint8 FireModeNum);

protected:
  UPROPERTY()
  UAbilityState* CurrentSate;

  UPROPERTY()
  uint8 CurrentFireMode;
  
  UPROPERTY()
  UAbilityState* ActiveState;

  UPROPERTY()
  UAbilityState* InactiveState;
	
};
