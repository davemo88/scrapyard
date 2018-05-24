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

// TODO: either make a blueprint for player controller to set the asset reference
// or do all the layout / styling / event binding in C++ 
	FStringClassReference MainMenuWidgetBPClassRef(TEXT("/Game/Levels/Main/MainMenuWidgetBP.MainMenuWidgetBP_C"));
	if (UClass* MainMenuWidgetBPClass = MainMenuWidgetBPClassRef.TryLoadClass<UMainMenuWidget>())
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetBPClass);
//		MainMenuWidget->AddToViewport();
	}
}


