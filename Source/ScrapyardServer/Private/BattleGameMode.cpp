// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameMode.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotPlayerController.h"


ABattleGameMode::ABattleGameMode()
{
	DefaultPawnClass = ARobotCharacter::StaticClass();
// don't need to mess with HUD I think
//	HUDClass = AHUD::StaticClass();
	PlayerControllerClass = ARobotPlayerController::StaticClass();
//	PlayerControllerClass = APlayerController::StaticClass();
//  GameStateClass = ABattleGameState::StaticClass();
//	PlayerStateClass = ABattlePlayerState::StaticClass();
//  SpectatorClass = ABattleSpectatorPawn::StaticClass();

//	bUseSeamlessTravel = true;
}
