// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityStateFiring.h"


void UAbilityStateFiring::BeginState(const UAbilityState* PrevState)
{
  UE_LOG(LogTemp, Warning, TEXT("UAbilityStateFiring::BeginState"));
//  GetOuterUScrapyardAbility()->OnStartedFiring; 
  FireShot();
}

void UAbilityStateFiring::EndState()
{
//  GetOuterUScrapyardAbility()->OnStoppedFiring()
}

bool UAbilityStateFiring::BeginFiringSequence(uint8 FireModeNum, bool bClientFired)
{
  if (bClientFired)
  {
  }
  return false;
}

void UAbilityStateFiring::FireShot()
{
  GetOuterUScrapyardAbility()->FireShot();
}

