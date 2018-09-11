// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrapyardAbility.h"
//#include "Ability/AbilityState.h"

void UScrapyardAbility::StartFire(uint8 FireModeNum)
{

}

void UScrapyardAbility::StopFire(uint8 FireModeNum)
{

}

void UScrapyardAbility::GotoState(UAbilityState* NewState)
{
  if (CurrentState != NewState)
  {
    UAbilityState* PrevState = CurrentState;
    if (CurrentState != NULL)
    {
      CurrentState->EndState();
    }
    if (CurrentState == PrevState)
    {
      CurrentState = NewState;
      CurrentState->BeginState(PrevState);

      StateChanged();
    }
  }
}

void UScrapyardAbility::GotoFireMode(uint8 NewFireMode)
{
 if (FiringState.IsValidIndex(NewFireMode))
 {
   CurrentFireMode = NewFireMode;
   GotoState(FiringState[NewFireMode]);
 }
}

bool UScrapyardAbility::BeginFiringSequence(uint8 FireModeNum, bool bClientFired)
{
  if (RobotOwner)
  {
    RobotOwner->SetPendingFire(FireModeNum, true);
    if (FiringState.IsValidIndex(FireModeNum))
    {
      FiringState[FireModeNum]->PendingFireStarted();
    }
    bool bResult = CurrentState->BeginFiringSequence(FireModeNum, bClientFired);
    return bResult;
  }
  return false;
}

void UScrapyardAbility::EndFiringSequence(uint8 FireModeNum)
{
  if (RobotOwner)
  {
    RobotOwner->SetPendingFire(FireModeNum, false);
  }
  if (FiringState.IsValidIndex(FireModeNum))
  {
    FiringState[FireModeNum]->PendingFireStopped();
  }
  CurrentState->EndFiringSequence(FireModeNum);
}

bool UScrapyardAbility::WillSpawnShot(float DeltaTime)
{
  return (CurrentState != NULL) && CanFireAgain() && CurrentState->WillSpawnShot(DeltaTime);
}

bool UScrapyardAbility::CanFireAgain()
{
  return true;
}
  
void UScrapyardAbility::FireShot()
{
  // can either override this on ability subclasses
  // or override FireProjectile / FireInstantHit etc
}

bool UScrapyardAbility::IsFiring() const
{
  return CurrentState->IsFiring();
}
