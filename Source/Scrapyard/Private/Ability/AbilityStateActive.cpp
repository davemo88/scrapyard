// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityStateActive.h"
#include "Ability/AbilityState.h"
#include "Ability/AbilityStateFiring.h"
#include "Ability/ScrapyardAbility.h"
#include "Robots/RobotCharacter.h"
#include "Player/RobotPlayerController.h"

void UAbilityStateActive::BeginState(const UAbilityState* PrevState)
{
  UE_LOG(LogTemp, Warning, TEXT("UAbilityStateActive::BeginState"));
  ARobotCharacter* RobotOwner = GetOuterAScrapyardAbility()->GetRobotOwner();

  for (uint8 i = 0; i <GetOuterAScrapyardAbility()->GetNumFireModes(); i++)
  {
    if (RobotOwner->IsPendingFire(i))
    {
      AScrapyardAbility* OuterAbility = GetOuterAScrapyardAbility();

      OuterAbility->CurrentFireMode = i; 
      OuterAbility->GotoState(OuterAbility->FiringState[i]); 

      return;
    }
  }
}

bool UAbilityStateActive::BeginFiringSequence(uint8 FireModeNum, bool bClientFired)
{
  UE_LOG(LogTemp, Warning, TEXT("UAbilityStateActive::BeginFiringSequence"));
  AScrapyardAbility* Ability = GetOuterAScrapyardAbility();
  if (Ability->FiringState.IsValidIndex(FireModeNum))
  {
    Ability->CurrentFireMode = FireModeNum;
    Ability->GotoState(Ability->FiringState[FireModeNum]);
    return true;
  }
  return false;
}

bool UAbilityStateActive::WillSpawnShot(float DeltaTime)
{
  ARobotPlayerController* PlayerController = Cast<ARobotPlayerController>(GetOuterAScrapyardAbility()->GetRobotOwner()->GetController());
  return false;
}
