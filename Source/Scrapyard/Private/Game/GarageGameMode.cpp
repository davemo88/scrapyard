// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageGameMode.h"
#include "Player/GaragePlayerController.h"
#include "Game/GarageGameState.h"

AGarageGameMode::AGarageGameMode()
{
  PlayerControllerClass = AGaragePlayerController::StaticClass();
  GameStateClass = AGarageGameState::StaticClass();
}
