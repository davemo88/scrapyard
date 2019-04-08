// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityState.h"
#include "Robots/RobotCharacter.h"
#include "Abilities/ScrapyardAbility.h"

ARobotCharacter* UAbilityState::GetRobotOwner()
{
  return GetOuterAScrapyardAbility()->GetRobotOwner();
}

UWorld* UAbilityState::GetWorld() const
{
  return GetOuterAScrapyardAbility()->GetWorld();
}

