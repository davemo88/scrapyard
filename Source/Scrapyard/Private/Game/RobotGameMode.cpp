// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotGameMode.h"
#include "Engine/Engine.h"
#include "UObjectGlobals.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Game/RobotGameState.h"
#include "Robots/RobotCharacter.h"
#include "UI/RobotHUD.h"
#include "Online/ScrapyardGameSession.h"
#include "Player/RobotPlayerController.h"
#include "Player/RobotPlayerState.h"

ARobotGameMode::ARobotGameMode()
{
  GameStateClass = ARobotGameState::StaticClass();
  DefaultPawnClass = ARobotCharacter::StaticClass();
  PlayerControllerClass = ARobotPlayerController::StaticClass();
  PlayerStateClass = ARobotPlayerState::StaticClass();
  HUDClass = ARobotHUD::StaticClass();
}

void ARobotGameMode::PostLogin(APlayerController* NewPlayer)
{
  UE_LOG(LogGameMode, Log, TEXT("%s::PostLogin"), *GetName());
  Super::PostLogin(NewPlayer);

}

TSubclassOf<AGameSession> ARobotGameMode::GetGameSessionClass() const
{
  return AScrapyardGameSession::StaticClass();
}
