// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityStateFiring.h"

void UAbilityStateFiring::BeginState(const UAbilityState* PrevState)
{
  UE_LOG(LogTemp, Warning, TEXT("UAbilityStateFiring::BeginState"));
//  GetOuterUScrapyardAbility()->OnStartedFiring; 

  UScrapyardAbility* Ability = GetOuterUScrapyardAbility();

  Ability->RobotOwner->GetWorldTimerManager().SetTimer(RefireCheckHandle, this, &UAbilityStateFiring::RefireCheckTimer, Ability->GetRefireTime(Ability->GetCurrentFireMode()), true);

  FireShot();
}

void UAbilityStateFiring::EndState()
{
  UE_LOG(LogTemp, Warning, TEXT("UAbilityStateFiring::EndState"));
//  GetOuterUScrapyardAbility()->OnStoppedFiring()
  GetOuterUScrapyardAbility()->RobotOwner->GetWorldTimerManager().ClearAllTimersForObject(this);
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

bool UAbilityStateFiring::WillSpawnShot(float DeltaTime)
{
  return GetOuterUScrapyardAbility()->GetRobotOwner()->IsPendingFire(GetOuterUScrapyardAbility()->GetCurrentFireMode());
}

void UAbilityStateFiring::RefireCheckTimer()
{
  GetRobotOwner()->SetPendingFire(GetOuterUScrapyardAbility()->GetCurrentFireMode(), false);
  GetOuterUScrapyardAbility()->GotoActiveState();
}
