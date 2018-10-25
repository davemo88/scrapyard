// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageGameMode.h"
#include "Player/GaragePlayerController.h"

AGarageGameMode::AGarageGameMode()
{
  PlayerControllerClass = AGaragePlayerController::StaticClass();
}
