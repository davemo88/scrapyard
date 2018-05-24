// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

class UMainMenuWidget;
/**
 * 
 */
UCLASS()
class SCRAPYARD_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

	AMenuPlayerController();

	void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	UPROPERTY()
	TSubclassOf<class UMainMenuWidget> wMainMenu;

	UMainMenuWidget* MainMenuWidget;
};
