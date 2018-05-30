// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuGameMode.h"
#include "Player/MainMenuPlayerController.h"
#include "Online/ScrapyardGameSession.h"


AMainMenuGameMode::AMainMenuGameMode()
{
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
}

void AMainMenuGameMode::RestartPlayer(class AController* NewPlayer)
{

}

TSubclassOf<AGameSession> AMainMenuGameMode::GetGameSessionClass() const
{
	return AScrapyardGameSession::StaticClass();
}

