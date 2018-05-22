// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPlayerController.h"
//#include "Robots/RobotCharacter.h"
#include "Robots/RobotPlayerCameraManager.h"

ARobotPlayerController::ARobotPlayerController()
{
	PlayerCameraManagerClass = ARobotPlayerCameraManager::StaticClass();
}

