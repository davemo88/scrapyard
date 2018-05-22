// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ScrapyardPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AScrapyardPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AScrapyardPlayerController();

	/** notify player about started match */
	UFUNCTION(reliable, client)
	void ClientGameStarted();

	/** Starts the online game using the session name in the PlayerState */
	UFUNCTION(reliable, client)
	void ClientStartOnlineGame();

	/** Ends the online game using the session name in the PlayerState */
	UFUNCTION(reliable, client)
	void ClientEndOnlineGame();	

	/** notify player about finished match */
	virtual void ClientGameEnded_Implementation(class AActor* EndGameFocus, bool bIsWinner);

//	/** sends cheat message */
//	UFUNCTION(reliable, server, WithValidation)
//	void ServerCheat(const FString& Msg);

	/** Local function say a string */
	UFUNCTION(exec)
	virtual void Say(const FString& Msg);

	/** RPC for clients to talk to server */
	UFUNCTION(unreliable, server, WithValidation)
	void ServerSay(const FString& Msg);	

	/** toggle InGameMenu handler */
//	void OnToggleInGameMenu();

	/** Show the in-game menu if it's not already showing */
//	void ShowInGameMenu();

	/** is game menu currently active? */
//	bool IsGameMenuVisible() const;	

	/** sets the produce force feedback flag. */
	void SetIsVibrationEnabled(bool bEnable);

	/** should produce force feedback? */
	bool IsVibrationEnabled() const;

	/** check if gameplay related actions (movement, weapon usage, etc) are allowed right now */
	bool IsGameInputAllowed() const;


	/** Ends and/or destroys game session */
	void CleanupSessionOnReturnToMenu();

	// Begin APlayerController interface

	/** Returns true if movement input is ignored. Overridden to always allow spectators to move. */
	virtual bool IsMoveInputIgnored() const override;

	/** Returns true if look input is ignored. Overridden to always allow spectators to look around. */
	virtual bool IsLookInputIgnored() const override;

	// End APlayerController interface

	// begin ARobotPlayerController-specific

	/** Cleans up any resources necessary to return to main menu.  Does not modify GameInstance state. */
	virtual void HandleReturnToMainMenu();

	/** Associate a new UPlayer with this PlayerController. */
	virtual void SetPlayer(UPlayer* Player);

	// end ARobotPlayerController-specific

protected:

	/** should produce force feedback? */
	uint8 bIsVibrationEnabled : 1;

	/** if set, gameplay related actions (movement, weapn usage, etc) are allowed */
	uint8 bAllowGameActions : 1;

	/** true for the first frame after the game has ended */
	uint8 bGameEndedFrame : 1;

	/** shooter in-game menu */
	TSharedPtr<class FScrapyardIngameMenu> ScrapyardIngameMenu;

	//Begin AActor interface

public:
//	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	//End AActor interface

	//Begin AController interface
	
	/** transition to dead state, retries spawning later */
	virtual void FailedToSpawnPawn() override;

	//End AController interface

	// Begin APlayerController interface

	/** respawn after dying */
	virtual void UnFreeze() override;

	/** sets up input */
	virtual void SetupInputComponent() override;

	/** Return the client to the main menu gracefully.  ONLY sets GI state. */
	void ClientReturnToMainMenu_Implementation(const FString& ReturnReason) override;

	/** Causes the player to commit suicide */
	UFUNCTION(exec)
	virtual void Suicide();

	/** Notifies the server that the client has suicided */
	UFUNCTION(reliable, server, WithValidation)
	void ServerSuicide();

	// End APlayerController interface

	FName	ServerSayString;

//	// Timer used for updating friends in the player tick.
//	float ScrapyardFriendUpdateTimer;

	// For tracking whether or not to send the end event
	bool bHasSentStartEvents;

	UPROPERTY(Transient, Replicated)
	bool BullshitReplicatedValue = true;

private:

	/** Handle for efficient management of ClientStartOnlineGame timer */
	FTimerHandle TimerHandle_ClientStartOnlineGame;

	
	
	
};
