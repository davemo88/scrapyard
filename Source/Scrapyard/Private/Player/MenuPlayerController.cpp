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
