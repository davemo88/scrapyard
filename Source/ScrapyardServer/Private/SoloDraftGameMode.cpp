// Fill out your copyright notice in the Description page of Project Settings.

#include "SoloDraftGameMode.h"
#include "Player/MenuPlayerController.h"

ASoloDraftGameMode::ASoloDraftGameMode()
{
	PlayerControllerClass = AMenuPlayerController::StaticClass();
}
