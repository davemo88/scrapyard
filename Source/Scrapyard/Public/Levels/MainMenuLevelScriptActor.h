// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Levels/ScrapyardLevelScriptActor.h"
//#include "UI/Menu/ScrapyardMainMenu.h"
#include "MainMenuLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AMainMenuLevelScriptActor : public AScrapyardLevelScriptActor
{
	GENERATED_BODY()

public:

	void PreInitializeComponents() override;

protected:

	void BeginPlay() override;
	
private:
	
};
