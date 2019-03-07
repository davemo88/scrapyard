// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ConstructorHelpers.h"
#include "UI/MainMenuWidget.h"


AMenuPlayerController::AMenuPlayerController()
{
  bDefaultShowMouseCursor = true;

  bShowMouseCursor = bDefaultShowMouseCursor;
  bEnableClickEvents = true;
  bEnableMouseOverEvents = true;

}

void AMenuPlayerController::PostInitializeComponents()
{
  Super::PostInitializeComponents();
}

void AMenuPlayerController::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();

  SetupWidget();

  OnWidgetReadyDelegate.Broadcast();
}

void AMenuPlayerController::ShowEscapeMenu()
{
  Super::ShowEscapeMenu();
}

void AMenuPlayerController::HideEscapeMenu()
{
  Super::HideEscapeMenu();
}
