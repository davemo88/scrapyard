// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameMode.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotPlayerController.h"


ABattleGameMode::ABattleGameMode()
{
	DefaultPawnClass = ARobotCharacter::StaticClass();
//	DefaultPawnClass = nullptr;

//	HUDClass = ABattleHUD::StaticClass();
	PlayerControllerClass = ARobotPlayerController::StaticClass();
	DefaultPawnClass = ARobotCharacter::StaticClass();
//	PlayerControllerClass = APlayerController::StaticClass();
//	PlayerStateClass = ARobotPlayerState::StaticClass();
//  SpectatorClass
//  GameStateClass::StaticClass();

//	bUseSeamlessTravel = true;
}
