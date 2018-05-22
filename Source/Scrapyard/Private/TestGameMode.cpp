// Fill out your copyright notice in the Description page of Project Settings.

#include "TestGameMode.h"
#include "MouseController.h"



ATestGameMode::ATestGameMode() {
	PlayerControllerClass = AMouseController::StaticClass();
}
