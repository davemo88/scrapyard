// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardPlayerController.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "Robots/RobotCharacter.h"
#include "UI/RobotHUDWidget.h"

void AScrapyardPlayerController::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();

//  SetupRobotHUDWidget();
}

//void AScrapyardPlayerController::SetupRobotHUDWidget()
//{
//  if (GetPawn())
//  {
//    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
//    RobotHUDWidget = CreateWidget<URobotHUDWidget>(this, GameInstance->DefaultAssetsBP->RobotHUDWidgetBP);
//    RobotHUDWidget->SetRobotCharacter(Cast<ARobotCharacter>(GetPawn()));
//    RobotHUDWidget->AddToViewport();
//  }
//}

void AScrapyardPlayerController::ClientSetupRobotHUDWidget_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ClientSetupRobotHUDWidget_Implementation"), *GetName());
  if (GetPawn())
  {
    UE_LOG(LogTemp, Warning, TEXT("pawn ok"));
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
    RobotHUDWidget = CreateWidget<URobotHUDWidget>(this, GameInstance->DefaultAssetsBP->RobotHUDWidgetBP);
    RobotHUDWidget->SetRobotCharacter(Cast<ARobotCharacter>(GetPawn()));
    RobotHUDWidget->AddToViewport();
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("pawn null"));
  }
}

