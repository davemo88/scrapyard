// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Robots/RobotPlayerState.h"
#include "BattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARDSERVER_API ABattleGameMode : public AGameMode
{
	GENERATED_BODY()

	ABattleGameMode();

public: 

	virtual void PreInitializeComponents() override;

	/** Initialize the game. This is called before actors' PreInitializeComponents. */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/** Accept or reject a player attempting to join the server.  Fails login if you set the ErrorMessage to a non-empty string. */
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	/** starts match warmup */
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/** always pick new random spawn */
	virtual bool ShouldSpawnAtStartSpot(AController* Player) override;

	/** notify about kills */
	virtual void Killed(AController* Killer, AController* KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType);

	/** can players damage each other? */
	virtual bool CanDealDamage(ARobotPlayerState* DamageInstigator, ARobotPlayerState* DamagedPlayer) const;

	/** update remaining time */
	virtual void DefaultTimer();

	/** called before startmatch */
	virtual void HandleMatchIsWaitingToStart() override;

	/** starts new match */
	virtual void HandleMatchHasStarted() override;

	/** returns default pawn class for given controller */
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	/** select best spawn point for player */
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	/** hides the onscreen hud and restarts the map */
	virtual void RestartGame() override;

protected:

	/** delay between first player login and starting match */
	UPROPERTY(config)
	int32 WarmupTime;

	/** match duration */
	UPROPERTY(config)
	int32 RoundTime;

	UPROPERTY(config)
	int32 TimeBetweenMatches;

	/** score for kill */
	UPROPERTY(config)
	int32 KillScore;

	/** score for death */
	UPROPERTY(config)
	int32 DeathScore;

	/** Handle for efficient management of DefaultTimer timer */
	FTimerHandle TimerHandle_DefaultTimer;

	/** Returns game session class to use */
	virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;	

	/** check who won */
	virtual void DetermineMatchWinner();

	/** check if PlayerState is a winner */
	virtual bool IsWinner(ARobotPlayerState* PlayerState) const;

public:	

	/** finish current match and lock players */
	UFUNCTION(exec)
	void FinishMatch();

	/*Finishes the match and bumps everyone to main menu.*/
	/*Only GameInstance should call this function */
	void RequestFinishAndExitToMainMenu();

};
