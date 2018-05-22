// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameState.h"
#include "GameFramework/Actor.h"
#include "Robots/RobotPlayerController.h"
#include "ScrapyardServer.h"
#include "BattleGameMode.h"
#include "ScrapyardGameInstance.h"


ABattleGameState::ABattleGameState()
{
	RemainingTime = 0;
	bTimerPaused = false;
}

void ABattleGameState::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( ABattleGameState, RemainingTime );
	DOREPLIFETIME( ABattleGameState, bTimerPaused );
}


void ABattleGameState::RequestFinishAndExitToMainMenu()
{
	if (AuthorityGameMode)
	{
		// we are server, tell the gamemode
		ABattleGameMode* const GameMode = Cast<ABattleGameMode>(AuthorityGameMode);
		if (GameMode)
		{
			GameMode->RequestFinishAndExitToMainMenu();
		}
	}
	else
	{
		// we are client, handle our own business
		UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());

		ARobotPlayerController* const PrimaryPC = Cast<ARobotPlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
		if (PrimaryPC)
		{
			check(PrimaryPC->GetNetMode() == ENetMode::NM_Client);
			PrimaryPC->HandleReturnToMainMenu();
		}
	}

}
