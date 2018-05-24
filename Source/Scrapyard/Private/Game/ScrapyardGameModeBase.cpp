// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardGameModeBase.h"
#include "Online/ScrapyardGameSession.h"


TSubclassOf<AGameSession> AScrapyardGameModeBase::GetGameSessionClass() const
{
	return AScrapyardGameSession::StaticClass();
}