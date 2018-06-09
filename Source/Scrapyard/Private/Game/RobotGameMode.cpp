// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotGameMode.h"
#include "Robots/RobotCharacter.h"
#include "Player/ScrapyardPlayerController.h"

ARobotGameMode::ARobotGameMode()
{
	DefaultPawnClass = ARobotCharacter::StaticClass();
	PlayerControllerClass = AScrapyardPlayerController::StaticClass();
}


