// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityState.h"
#include "Ability/ScrapyardAbility.h"

ARobotCharacter* UAbilityState::GetRobotOwner()
{
  return GetOuterAScrapyardAbility()->GetRobotOwner();
}

UWorld* UAbilityState::GetWorld() const
{
  return GetOuterAScrapyardAbility()->GetWorld();
}

