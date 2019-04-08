// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityStateFiring.h"

void UAbilityStateFiring::BeginState(const UAbilityState* PrevState)
{
  UE_LOG(LogTemp, Warning, TEXT("UAbilityStateFiring::BeginState"));
//  GetOuterAScrapyardAbility()->OnStartedFiring; 

  AScrapyardAbility* Ability = GetOuterAScrapyardAbility();

  Ability->RobotOwner->GetWorldTimerManager().SetTimer(RefireCheckHandle, this, &UAbilityStateFiring::RefireCheckTimer, Ability->GetRefireTime(Ability->GetCurrentFireMode()), true);

  FireShot();
}

void UAbilityStateFiring::EndState()
{
  UE_LOG(LogTemp, Warning, TEXT("UAbilityStateFiring::EndState"));
//  GetOuterAScrapyardAbility()->OnStoppedFiring()
  GetOuterAScrapyardAbility()->RobotOwner->GetWorldTimerManager().ClearAllTimersForObject(this);
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
  GetOuterAScrapyardAbility()->FireShot();
}

bool UAbilityStateFiring::WillSpawnShot(float DeltaTime)
{
  return GetOuterAScrapyardAbility()->GetRobotOwner()->IsPendingFire(GetOuterAScrapyardAbility()->GetCurrentFireMode());
}

void UAbilityStateFiring::RefireCheckTimer()
{
  GetRobotOwner()->SetPendingFire(GetOuterAScrapyardAbility()->GetCurrentFireMode(), false);
  GetOuterAScrapyardAbility()->GotoActiveState();
}
