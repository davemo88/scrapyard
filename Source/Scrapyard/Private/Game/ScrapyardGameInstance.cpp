// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardGameInstance.h"

UScrapyardGameInstance::UScrapyardGameInstance()
{
// TODO: find the right place for these
	RobotPartAssignment = CreateDefaultSubobject<URobotPartAssignment>(TEXT("RobotPartAssignment"));
	SoloDraft = CreateDefaultSubobject<USoloDraft>(TEXT("SoloDraft"));
};

AScrapyardGameSession* UScrapyardGameInstance::GetGameSession() const
{
	UWorld* const World = GetWorld();
	if (World)
	{
		AGameModeBase* const Game = World->GetAuthGameMode();
		if (Game)
		{
			return Cast<AScrapyardGameSession>(Game->GameSession);
		}
	}

	return nullptr;
}


void UScrapyardGameInstance::Init()
{
	Super::Init();
}

void UScrapyardGameInstance::Shutdown()
{
	Super::Shutdown();
}

FGameInstancePIEResult UScrapyardGameInstance::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
{
	UE_LOG(LogTemp, Warning, TEXT("StartPlayInEditorGameInstance()"));
	return Super::StartPlayInEditorGameInstance(LocalPlayer, Params);
}

void UScrapyardGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}