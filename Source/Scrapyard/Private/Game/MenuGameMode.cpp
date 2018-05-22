// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuGameMode.h"
#include "Player/MenuPlayerController.h"
#include "Online/ScrapyardGameSession.h"


AMenuGameMode::AMenuGameMode()
{
	PlayerControllerClass = AMenuPlayerController::StaticClass();
}

void AMenuGameMode::RestartPlayer(class AController* NewPlayer)
{

}

TSubclassOf<AGameSession> AMenuGameMode::GetGameSessionClass() const
{
	return AScrapyardGameSession::StaticClass();
}

