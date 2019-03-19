// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotGameMode.h"
#include "Engine/Engine.h"
#include "UObjectGlobals.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Robots/RobotCharacter.h"
#include "UI/RobotHUD.h"
#include "Online/ScrapyardGameSession.h"
#include "Player/RobotPlayerController.h"

ARobotGameMode::ARobotGameMode()
{
  DefaultPawnClass = ARobotCharacter::StaticClass();
  PlayerControllerClass = ARobotPlayerController::StaticClass();
  HUDClass = ARobotHUD::StaticClass();
}

void ARobotGameMode::PostLogin(APlayerController* NewPlayer)
{
  Super::PostLogin(NewPlayer);

  UE_LOG(LogTemp, Warning, TEXT("A player has logged in"));
}

TSubclassOf<AGameSession> ARobotGameMode::GetGameSessionClass() const
{
  return AScrapyardGameSession::StaticClass();
}
