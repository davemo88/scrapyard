// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BattleGameState.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARDSERVER_API ABattleGameState : public AGameState
{
	GENERATED_BODY()
			
public:

	ABattleGameState();

	/** time left for warmup / match */
	UPROPERTY(Transient, Replicated)
	int32 RemainingTime;

	/** is timer paused? */
	UPROPERTY(Transient, Replicated)
	bool bTimerPaused;

	void RequestFinishAndExitToMainMenu();
	
};
