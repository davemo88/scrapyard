// Fill out your copyright notice in the Description page of Project Settings.

#include "GaragePlayerController.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "UObjectGlobals.h"
#include "Blueprint/UserWidget.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "Robots/RobotBodyGarage.h"
#include "UI/GarageWidget.h"

void AGaragePlayerController::BeginPlay()
{
  Super::BeginPlay();

  SetupGarageWidget();
}

void AGaragePlayerController::SetupGarageWidget()
{
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  GarageWidget = CreateWidget<UGarageWidget>(this, GameInstance->DefaultAssetsBP->GarageWidgetBP);
  GarageWidget->AddToViewport();
}

