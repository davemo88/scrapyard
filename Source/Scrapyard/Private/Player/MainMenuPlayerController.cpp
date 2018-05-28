// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuPlayerController.h"
#include "UI/MainMenuWidget.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

// TODO: get from game instance default assets
// https://forums.unrealengine.com/development-discussion/c-gameplay-programming/42318-opening-a-widget-blueprint-from-c-code
	FStringClassReference MainMenuWidgetBPClassRef(TEXT("/Game/Levels/Main/MainMenuWidgetBP.MainMenuWidgetBP_C"));
	if (UClass* MainMenuWidgetBPClass = MainMenuWidgetBPClassRef.TryLoadClass<UMainMenuWidget>())
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetBPClass);
		MainMenuWidget->AddToViewport();
	}
}


