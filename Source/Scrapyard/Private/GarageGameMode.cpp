// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageGameMode.h"
#include "Player/MenuPlayerController.h"

AGarageGameMode::AGarageGameMode()
{
	PlayerControllerClass = AMenuPlayerController::StaticClass();
}