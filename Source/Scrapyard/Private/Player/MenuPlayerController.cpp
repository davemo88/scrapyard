// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ConstructorHelpers.h"
#include "UI/MainMenuWidget.h"


AMenuPlayerController::AMenuPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

}

void AMenuPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

// TODO: either make a blueprint to set the asset references
// or do all the layout / styling / event binding in C++ 
// https://forums.unrealengine.com/development-discussion/c-gameplay-programming/42318-opening-a-widget-blueprint-from-c-code
	FStringClassReference MainMenuWidgetBPClassRef(TEXT("/Game/Levels/Main/MainMenuWidgetBP.MainMenuWidgetBP_C"));
	if (UClass* MainMenuWidgetBPClass = MainMenuWidgetBPClassRef.TryLoadClass<UMainMenuWidget>())
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetBPClass);
		MainMenuWidget->AddToViewport();
	}
}
