// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotGameState.h"
#include "Targeting/TargetableInterface.h"
#include "Engine/World.h"
#include "TimerManager.h"

void ARobotGameState::MulticastStartMatchTimer_Implementation(uint32 Seconds)
{
  bMatchTimerExpired = false;
  UE_LOG(LogGameState, Log, TEXT("%s::MulticastStartMatchTimer"), *GetName());
  UE_LOG(LogGameState, Log, TEXT("%s::MulticastStartMatchTimer - %d Seconds"), *GetName(), Seconds);
  MatchTimerSecondsRemaining = Seconds;
  GetWorld()->GetTimerManager().SetTimer(MatchTimerHandle, this, &ARobotGameState::MatchTimer, 1.0f, true);
  OnMatchTimerStartedDelegate.Broadcast();
}

void ARobotGameState::MulticastStopMatchTimer_Implementation()
{
//TODO: clear delegates and stop the timer
  UE_LOG(LogGameState, Log, TEXT("%s::MulticastStopMatchTimer"), *GetName());
  GetWorld()->GetTimerManager().ClearTimer(MatchTimerHandle);
  OnMatchTimerStoppedDelegate.Broadcast();
}

void ARobotGameState::MatchTimer()
{
  UE_LOG(LogGameState, VeryVerbose, TEXT("%s::MatchTimer"), *GetName());
  if (MatchTimerSecondsRemaining > 0)
  {
    MatchTimerSecondsRemaining--;
    OnMatchTimerUpdatedDelegate.Broadcast();
    if (MatchTimerSecondsRemaining == 0)
    {
      UE_LOG(LogGameState, Log, TEXT("%s::MatchTimer - Timer Expired"), *GetName());
      GetWorld()->GetTimerManager().ClearTimer(MatchTimerHandle);
      bMatchTimerExpired = true;
      OnMatchTimerExpiredDelegate.Broadcast();      
    }
  }
}

uint32 ARobotGameState::GetMatchTimerSecondsRemaining() const
{
  return MatchTimerSecondsRemaining;
}

bool ARobotGameState::IsMatchTimerActive() const
{
  return GetWorld()->GetTimerManager().IsTimerActive(MatchTimerHandle);
}

bool ARobotGameState::IsMatchTimerExpired() const
{
  return bMatchTimerExpired;
}

void ARobotGameState::MulticastAddTargetable_Implementation(AActor* Actor)
{
  AddTargetable(Actor);
}

void ARobotGameState::MulticastRemoveTargetable_Implementation(AActor* Actor)
{
  RemoveTargetable(Actor);
}

void ARobotGameState::AddTargetable(AActor* Actor)
{
  if (Cast<ITargetableInterface>(Actor))
  {
    TargetableActors.AddUnique(Actor);
    OnTargetableAddedDelegate.Broadcast(Actor);
  }
}

void ARobotGameState::RemoveTargetable(AActor* Actor)
{
  TargetableActors.Remove(Actor);
  OnTargetableRemovedDelegate.Broadcast(Actor);
}

void ARobotGameState::MulticastReadyToStartMatch_Implementation(bool bReady)
{
  UE_LOG(LogGameState, Log, TEXT("%s::MulticastReadyToStartMatch"), *GetName());
  OnReadyToStartMatchDelegate.Broadcast(bReady);
}
