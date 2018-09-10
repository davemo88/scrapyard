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
