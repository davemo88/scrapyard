// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameState.h"
#include "Player/RobotPlayerController.h"

ABattleGameState::ABattleGameState()
{
}

void ABattleGameState::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();

//BUG: doesn't work when hosting a listen server, e.g. in development
  if (!HasAuthority())
  {
    UWorld* World = GetWorld();
    ARobotPlayerController* RobotPC = World->GetFirstPlayerController<ARobotPlayerController>();
    if (RobotPC)
    {
      RobotPC->ServerNotifyGameStateReplicated();
      OnLeavingMapDelegate.AddDynamic(RobotPC->MatchStatusWidget, &UMatchStatusWidget::ShowScreenBlocker);
    }

  }
// for development testing in editor
  else if (GetNetMode() == ENetMode::NM_Standalone)
  {
    UE_LOG(LogTemp, Warning, TEXT("Local Net Mode"));    
    UWorld* World = GetWorld();
    ARobotPlayerController* RobotPC = World->GetFirstPlayerController<ARobotPlayerController>();
    if (RobotPC)
    {
      RobotPC->ServerNotifyGameStateReplicated();
    }
  }
}

void ABattleGameState::HandleMatchIsWaitingToStart()
{
  Super::HandleMatchIsWaitingToStart();
  UE_LOG(LogTemp, Warning, TEXT("%s::HandleMatchIsWaitingToStart"), *GetName());

  if (!HasAuthority() || GetNetMode() == ENetMode::NM_Standalone)
  {
    UWorld* World = GetWorld();
    ARobotPlayerController* RobotPC = World->GetFirstPlayerController<ARobotPlayerController>();
    if (RobotPC)
    {
      RobotPC->MatchStatusWidget->SetAnnouncement(NSLOCTEXT("SY","WaitingToStartAnnouncement","Waiting To Start Battle"));
    }
  }
}

void ABattleGameState::HandleMatchHasStarted()
{
  Super::HandleMatchHasStarted();
  UE_LOG(LogTemp, Warning, TEXT("%s::HandleMatchHasStarted"), *GetName());

  if (!HasAuthority() || GetNetMode() == ENetMode::NM_Standalone)
  {
    UWorld* World = GetWorld();
    ARobotPlayerController* RobotPC = World->GetFirstPlayerController<ARobotPlayerController>();
    if (RobotPC)
    {
      RobotPC->MatchStatusWidget->SetAnnouncement(NSLOCTEXT("SY","BattleStartAnnouncement","Battle!"));
    }
  }
}

void ABattleGameState::HandleMatchHasEnded()
{
  Super::HandleMatchHasEnded();
  UE_LOG(LogTemp, Warning, TEXT("%s::HandleMatchHasEnded"), *GetName());

  if (!HasAuthority() || GetNetMode() == ENetMode::NM_Standalone)
  {
    UWorld* World = GetWorld();
    ARobotPlayerController* RobotPC = World->GetFirstPlayerController<ARobotPlayerController>();
    if (RobotPC)
    {
      RobotPC->MatchStatusWidget->SetAnnouncement(NSLOCTEXT("SY","BattleEndedAccouncement","Battle Has Ended"));
      RobotPC->MatchStatusWidget->ShowScreenBlocker();
      RobotPC->RobotHUDWidget->SetVisibility(ESlateVisibility::Hidden);
    }
  }
}

void ABattleGameState::HandleLeavingMap()
{
  Super::HandleLeavingMap();
  UE_LOG(LogTemp, Warning, TEXT("%s::HandleLeavingMap"), *GetName());

  if (!HasAuthority() || GetNetMode() == ENetMode::NM_Standalone)
  {
    UWorld* World = GetWorld();
    ARobotPlayerController* RobotPC = World->GetFirstPlayerController<ARobotPlayerController>();
    if (RobotPC)
    {
      RobotPC->MatchStatusWidget->SetAnnouncement(NSLOCTEXT("SY","LeavingMapAnnouncement","Leaving Map"));
    }
  }
}

void ABattleGameState::MulticastBroadcastLeavingMap_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::MulticastBroadcastLeavingMap"), *GetName());
  OnLeavingMapDelegate.Broadcast();
}
