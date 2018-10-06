// Fill out your copyright notice in the Description page of Project Settings.

#include "SoloDraftGameMode.h"
#include "Player/SoloDraftPlayerController.h"

ASoloDraftGameMode::ASoloDraftGameMode()
{
  PlayerControllerClass = ASoloDraftPlayerController::StaticClass();
}
