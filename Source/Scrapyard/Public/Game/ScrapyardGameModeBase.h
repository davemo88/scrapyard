// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ScrapyardGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AScrapyardGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;	
	
};
