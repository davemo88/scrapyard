// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameState.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Player/RobotPlayerController.h"

ABattleGameState::ABattleGameState()
{
}

void ABattleGameState::BeginPlay()
{
  UE_LOG(LogGameState, Log, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();

//BUG: doesn't work when hosting a listen server, e.g. in development
  if (!HasAuthority())
  {
    UE_LOG(LogGameState, Log, TEXT("!HasAuthority() == true"));    
    UWorld* World = GetWorld();
    ARobotPlayerController* RobotPC = World->GetFirstPlayerController<ARobotPlayerController>();
    if (RobotPC)
    {
      RobotPC->ServerNotifyGameStateReplicated();
      OnLeavingMapDelegate.AddDynamic(RobotPC->MatchStatusWidget, &UMatchStatusWidget::ShowScreenBlocker);
    }

  }
// for development testing in editor
  else if (GetNetMode() == ENetMode::NM_Standalone || GetNetMode() == ENetMode::NM_Client)
  {
    UE_LOG(LogGameState, Log, TEXT("Local Net Mode"));    
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
  UE_LOG(LogGameState, Log, TEXT("%s::HandleMatchIsWaitingToStart"), *GetName());

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
  UE_LOG(LogGameState, Log, TEXT("%s::HandleMatchHasStarted"), *GetName());

  if (!HasAuthority() || GetNetMode() == ENetMode::NM_Standalone)
  {
    UWorld* World = GetWorld();
    ARobotPlayerController* RobotPC = World->GetFirstPlayerController<ARobotPlayerController>();
    if (RobotPC)
    {
      RobotPC->MatchStatusWidget->SetAnnouncement(NSLOCTEXT("SY","BattleStartAnnouncement","Battle!"));
//TODO: clean up this hack
      const FVector2D ViewCenter = UWidgetLayoutLibrary::GetViewportSize(GetWorld())/2;
      RobotPC->SetMouseLocation(ViewCenter.X, ViewCenter.Y);
    }
  }
}

void ABattleGameState::HandleMatchHasEnded()
{
  Super::HandleMatchHasEnded();
  UE_LOG(LogGameState, Log, TEXT("%s::HandleMatchHasEnded"), *GetName());

  if (!HasAuthority() || GetNetMode() == ENetMode::NM_Standalone)
  {
    UWorld* World = GetWorld();
    ARobotPlayerController* RobotPC = World->GetFirstPlayerController<ARobotPlayerController>();
    if (RobotPC)
    {
      if (RobotPC->MatchStatusWidget)
      {
        RobotPC->MatchStatusWidget->SetAnnouncement(NSLOCTEXT("SY","BattleEndedAccouncement","Battle Has Ended"));
        RobotPC->MatchStatusWidget->ShowScreenBlocker();
      }
      if (RobotPC->RobotHUDWidget)
      {
        RobotPC->RobotHUDWidget->SetVisibility(ESlateVisibility::Hidden);
      }
    }
  }
}

void ABattleGameState::HandleLeavingMap()
{
  Super::HandleLeavingMap();
  UE_LOG(LogGameState, Log, TEXT("%s::HandleLeavingMap"), *GetName());

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
  UE_LOG(LogGameState, Log, TEXT("%s::MulticastBroadcastLeavingMap"), *GetName());
  OnLeavingMapDelegate.Broadcast();
}
