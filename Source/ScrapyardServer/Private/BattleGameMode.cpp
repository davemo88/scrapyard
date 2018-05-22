// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGameMode.h"
#include "CoreMinimal.h"
//#include "Online.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotPlayerController.h"
#include "ScrapyardGameInstance.h"
#include "BattleGameState.h"
#include "ScrapyardGameSession.h"


ABattleGameMode::ABattleGameMode()
{
	DefaultPawnClass = ARobotCharacter::StaticClass();
//	DefaultPawnClass = nullptr;

//	HUDClass = ABattleHUD::StaticClass();
	PlayerControllerClass = ARobotPlayerController::StaticClass();
//	PlayerControllerClass = APlayerController::StaticClass();
//	PlayerStateClass = ARobotPlayerState::StaticClass();
//  SpectatorClass
//  GameStateClass::StaticClass();

	bUseSeamlessTravel = true;
}

void ABattleGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	GetWorldTimerManager().SetTimer(TimerHandle_DefaultTimer, this, &ABattleGameMode::DefaultTimer, GetWorldSettings()->GetEffectiveTimeDilation(), true);
}

void ABattleGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

//	const UGameInstance* GameInstance = GetGameInstance();
//	if (GameInstance && Cast<UShooterGameInstance>(GameInstance)->GetOnlineMode() != EOnlineMode::Offline)
//	{
//		bPauseable = false;
//	}
}

void ABattleGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	ABattleGameState* const MyGameState = Cast<ABattleGameState>(GameState);
	const bool bMatchIsOver = MyGameState && MyGameState->HasMatchEnded();
	if( bMatchIsOver )
	{
		ErrorMessage = TEXT("Match is over!");
	}
	else
	{
		// GameSession can be NULL if the match is over
		Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	}
}


void ABattleGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// update spectator location for client
	ARobotPlayerController* NewPC = Cast<ARobotPlayerController>(NewPlayer);
	if (NewPC && NewPC->GetPawn() == NULL)
	{
// TODO: spectators n stuff
//		NewPC->ClientSetSpectatorCamera(NewPC->GetSpawnLocation(), NewPC->GetControlRotation());
	}

	// notify new player if match is already in progress
	if (NewPC && IsMatchInProgress())
	{
		NewPC->ClientGameStarted();
		NewPC->ClientStartOnlineGame();
	}
}

/** Returns game session class to use */
TSubclassOf<AGameSession> ABattleGameMode::GetGameSessionClass() const
{
	return AScrapyardGameSession::StaticClass();
}

void ABattleGameMode::DefaultTimer()
{
	// don't update timers for Play In Editor mode, it's not real match
	if (GetWorld()->IsPlayInEditor())
	{
		// start match if necessary.
		if (GetMatchState() == MatchState::WaitingToStart)
		{
			StartMatch();
		}
		return;
	}

	ABattleGameState* const BattleGameState = Cast<ABattleGameState>(GameState);
	if (BattleGameState && BattleGameState->RemainingTime > 0 && !BattleGameState->bTimerPaused)
	{
		BattleGameState->RemainingTime--;
		
		if (BattleGameState->RemainingTime <= 0)
		{
			if (GetMatchState() == MatchState::WaitingPostMatch)
			{
				RestartGame();
			}
			else if (GetMatchState() == MatchState::InProgress)
			{
				FinishMatch();

				// Send end round events
				for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
				{
					ARobotPlayerController* PlayerController = Cast<ARobotPlayerController>(*It);
					
					if (PlayerController && BattleGameState)
					{
						ARobotPlayerState* PlayerState = Cast<ARobotPlayerState>((*It)->PlayerState);
//						const bool bIsWinner = IsWinner(PlayerState);
					
//						PlayerController->ClientSendRoundEndEvent(bIsWinner, MyBattleGameState->ElapsedTime);
					}
				}
			}
			else if (GetMatchState() == MatchState::WaitingToStart)
			{
				StartMatch();
			}
		}
	}
}

void ABattleGameMode::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();

	if (bDelayedStart)
	{
		// start warmup if needed
		ABattleGameState* const MyGameState = Cast<ABattleGameState>(GameState);
		if (MyGameState && MyGameState->RemainingTime == 0)
		{
			const bool bWantsMatchWarmup = !GetWorld()->IsPlayInEditor();
			if (bWantsMatchWarmup && WarmupTime > 0)
			{
				MyGameState->RemainingTime = WarmupTime;
			}
			else
			{
				MyGameState->RemainingTime = 0.0f;
			}
		}
	}
}

void ABattleGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	ABattleGameState* const MyGameState = Cast<ABattleGameState>(GameState);
	MyGameState->RemainingTime = RoundTime;	

	// notify players
	for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ARobotPlayerController* PC = Cast<ARobotPlayerController>(*It);
		if (PC)
		{
			PC->ClientGameStarted();
		}
	}
}

void ABattleGameMode::FinishMatch()
{
	ABattleGameState* const MyGameState = Cast<ABattleGameState>(GameState);
	if (IsMatchInProgress())
	{
		EndMatch();

		// notify players
		for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
		{
			ARobotPlayerState* PlayerState = Cast<ARobotPlayerState>((*It)->PlayerState);

			(*It)->GameHasEnded(NULL);
		}

		// lock all pawns
		// pawns are not marked as keep for seamless travel, so we will create new pawns on the next match rather than
		// turning these back on.
		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			(*It)->TurnOff();
		}

		// set up to restart the match
		MyGameState->RemainingTime = TimeBetweenMatches;
	}
}

void ABattleGameMode::RequestFinishAndExitToMainMenu()
{
	FinishMatch();

	UScrapyardGameInstance* const GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());

	ARobotPlayerController* LocalPrimaryController = nullptr;
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		ARobotPlayerController* Controller = Cast<ARobotPlayerController>(*Iterator);

		if (Controller == NULL)
		{
			continue;
		}

		if (!Controller->IsLocalController())
		{
			const FString RemoteReturnReason = NSLOCTEXT("NetworkErrors", "HostHasLeft", "Host has left the game.").ToString();
			Controller->ClientReturnToMainMenu(RemoteReturnReason);
		}
		else
		{
			LocalPrimaryController = Controller;
		}
	}

	// GameInstance should be calling this from an EndState.  So call the PC function that performs cleanup, not the one that sets GI state.
	if (LocalPrimaryController != NULL)
	{
		LocalPrimaryController->HandleReturnToMainMenu();
	}
}

void ABattleGameMode::DetermineMatchWinner()
{
	// nothing to do here
}

bool ABattleGameMode::IsWinner(class ARobotPlayerState* PlayerState) const
{
	return false;
}

void ABattleGameMode::Killed(AController* Killer, AController* KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType)
{
	ARobotPlayerState* KillerPlayerState = Killer ? Cast<ARobotPlayerState>(Killer->PlayerState) : NULL;
	ARobotPlayerState* VictimPlayerState = KilledPlayer ? Cast<ARobotPlayerState>(KilledPlayer->PlayerState) : NULL;

	if (KillerPlayerState && KillerPlayerState != VictimPlayerState)
	{
//		KillerPlayerState->ScoreKill(VictimPlayerState, KillScore);
//		KillerPlayerState->InformAboutKill(KillerPlayerState, DamageType, VictimPlayerState);
	}

	if (VictimPlayerState)
	{
//		VictimPlayerState->ScoreDeath(KillerPlayerState, DeathScore);
//		VictimPlayerState->BroadcastDeath(KillerPlayerState, DamageType, VictimPlayerState);
	}
}

bool ABattleGameMode::CanDealDamage(class ARobotPlayerState* DamageInstigator, class ARobotPlayerState* DamagedPlayer) const
{
	return true;
}

bool ABattleGameMode::ShouldSpawnAtStartSpot(AController* Player)
{
	return false;
}

UClass* ABattleGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

AActor* ABattleGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	return Super::ChoosePlayerStart_Implementation(Player);
}

void ABattleGameMode::RestartGame()
{
	Super::RestartGame();
}
