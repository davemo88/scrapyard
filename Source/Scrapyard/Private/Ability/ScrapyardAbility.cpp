// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrapyardAbility.h"
#include "Ability/AbilityState.h"
#include "Ability/AbilityStateActive.h"
#include "Ability/AbilityStateInactive.h"
#include "Ability/AbilityStateFiring.h"

UScrapyardAbility::UScrapyardAbility()
{
  UE_LOG(LogTemp, Warning, TEXT("UScrapyardAbility::UScrapyardAbility"));
  InactiveState = CreateDefaultSubobject<UAbilityStateInactive>(TEXT("AbilityStateInactive"));
  ActiveState = CreateDefaultSubobject<UAbilityStateActive>(TEXT("AbilityStateActive"));

  FiringState.Add(CreateDefaultSubobject<UAbilityStateFiring>(TEXT("FiringState0")));
  FireInterval.Add(1.0f);

  CurrentState = ActiveState;

  AbilityName = TEXT("ScrapyardAbility");

}

void UScrapyardAbility::StartFire(uint8 FireModeNum)
{
  
  UE_LOG(LogTemp,Warning,TEXT("UScrapyardAbility::StartFire"));

  bool bClientFired = BeginFiringSequence(FireModeNum, false);

  if (RobotOwner->Role < ROLE_Authority)
  {
    UAbilityStateFiring* CurrentFiringState = FiringState.IsValidIndex(FireModeNum) ? FiringState[FireModeNum] : nullptr;  
    if (CurrentFiringState)
    {
      FireEventIndex++;
      if (FireEventIndex == 255)
      {
        FireEventIndex = 0;
      }
    }
    ServerStartFire(FireModeNum, FireEventIndex, bClientFired);
  }
}

void UScrapyardAbility::StopFire(uint8 FireModeNum)
{
  UE_LOG(LogTemp,Warning,TEXT("UScrapyardAbility::StopFire"));
  EndFiringSequence(FireModeNum);
  if (RobotOwner->Role < ROLE_Authority)
  {
    UAbilityStateFiring* CurrentFiringState = FiringState.IsValidIndex(FireModeNum) ? FiringState[FireModeNum] : nullptr;
    if (CurrentFiringState)
    {
      FireEventIndex++;
      if (FireEventIndex == 255)
      {
        FireEventIndex = 0;
      }
    }
    ServerStopFire(FireModeNum, FireEventIndex);
  }
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

void UScrapyardAbility::GotoActiveState()
{
  GotoState(ActiveState);
}

void UScrapyardAbility::GotoFireMode(uint8 NewFireMode)
{
 UE_LOG(LogTemp,Warning,TEXT("UScrapyardAbility::GotoFireMode"));
 if (FiringState.IsValidIndex(NewFireMode))
 {
   CurrentFireMode = NewFireMode;
   GotoState(FiringState[NewFireMode]);
 }
}

bool UScrapyardAbility::BeginFiringSequence(uint8 FireModeNum, bool bClientFired)
{
  UE_LOG(LogTemp,Warning,TEXT("UScrapyardAbility::BeginFiringSequence"));
  if (RobotOwner != NULL)
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
  UE_LOG(LogTemp,Warning,TEXT("UScrapyardAbility::EndFiringSequence"));
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

float UScrapyardAbility::GetRefireTime(uint8 FireModeNum)
{
  float RefireTime = 0.1f;

  if (FireInterval.IsValidIndex(FireModeNum))
  {
    RefireTime = FireInterval[FireModeNum];
  }

  return RefireTime;

}

void UScrapyardAbility::ServerStartFire_Implementation(uint8 FireModeNum, uint8 InFireEventIndex, bool bClientFired)
{
  UE_LOG(LogTemp, Warning, TEXT("UScrapyardAbility::ServerStartFire_Implementation"));

  BeginFiringSequence(FireModeNum, bClientFired);
}

bool UScrapyardAbility::ServerStartFire_Validate(uint8 FireModeNum, uint8 InFireEventIndex, bool bClientFired)
{
  UE_LOG(LogTemp, Warning, TEXT("UScrapyardAbility::ServerStartFire_Validate"));
  return true;
}

void UScrapyardAbility::ServerStopFire_Implementation(uint8 FireModeNum, uint8 InFireEventIndex)
{
  EndFiringSequence(FireModeNum);
}

bool UScrapyardAbility::ServerStopFire_Validate(uint8 FireModeNum, uint8 InFireEventIndex)
{
  return true;
}
