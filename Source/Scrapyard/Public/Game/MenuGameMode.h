// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AMenuGameMode();

	virtual void RestartPlayer(class AController* NewPlayer) override;

	virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;

protected:

	void BeginSession();

	void ShowLoadingScreen();
};
