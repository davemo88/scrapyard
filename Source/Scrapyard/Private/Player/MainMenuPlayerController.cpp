// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuPlayerController.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "UI/MainMenuWidget.h"

void AMainMenuPlayerController::BeginPlay()
{
  Super::BeginPlay();
  SetupMainMenuWidget();
}

void AMainMenuPlayerController::SetupMainMenuWidget()
{
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  MainMenuWidget = CreateWidget<UMainMenuWidget>(this, GameInstance->AssetsBP->UIAssetsBP->MainMenuWidgetBP);
  MainMenuWidget->AddToViewport();
}

void AMainMenuPlayerController::ShowEscapeMenu()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ShowEscapeMenu"), *StaticClass()->GetFName().ToString());
  Super::ShowEscapeMenu();
//  bEnableClickEvents = true;
//  bEnableMouseOverEvents = true;
}

void AMainMenuPlayerController::HideEscapeMenu()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::HideEscapeMenu"), *StaticClass()->GetFName().ToString());
  MainMenuWidget->SetUserFocus(this);
  Super::HideEscapeMenu();
}
