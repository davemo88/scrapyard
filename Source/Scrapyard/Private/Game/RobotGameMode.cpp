// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotGameMode.h"
#include "Robots/RobotCharacter.h"

ARobotGameMode::ARobotGameMode()
{
	DefaultPawnClass = ARobotCharacter::StaticClass();
}


