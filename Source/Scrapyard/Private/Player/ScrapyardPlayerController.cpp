// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardPlayerController.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "UI/EscapeMenuWidget.h"
#include "Robots/RobotCharacter.h"
#include "UI/RobotHUDWidget.h"
#include "GameFramework/PlayerController.h"

void AScrapyardPlayerController::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();

  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  EscapeMenuWidget = CreateWidget<UEscapeMenuWidget>(this, GameInstance->DefaultAssetsBP->EscapeMenuWidgetBP);

}

void AScrapyardPlayerController::SetupInputComponent()
{
  Super::SetupInputComponent();
  InputComponent->BindAction("Escape",IE_Pressed, this, &AScrapyardPlayerController::ToggleEscapeMenu);

}

void AScrapyardPlayerController::ToggleEscapeMenu()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ToggleEscapeMenu"), *GetName());
  if (EscapeMenuWidget->IsInViewport())
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::ToggleEscapeMenu - Toggle Off"), *GetName());
    EscapeMenuWidget->RemoveFromViewport();
    ClientIgnoreLookInput(false);
    const FInputModeGameOnly InputMode = FInputModeGameOnly();
    SetInputMode(InputMode);
    bShowMouseCursor = false;
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::ToggleEscapeMenu - Toggle On"), *GetName());
    EscapeMenuWidget->AddToViewport();
    ClientIgnoreLookInput(true);
    const FInputModeGameAndUI InputMode = FInputModeGameAndUI();
    SetInputMode(InputMode);
    bShowMouseCursor = true;
    
  }
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
//
//void AScrapyardPlayerController::ClientSetupRobotHUDWidget_Implementation()
//{
//  UE_LOG(LogTemp, Warning, TEXT("%s::ClientSetupRobotHUDWidget_Implementation"), *GetName());
//  if (GetPawn())
//  {
//    UE_LOG(LogTemp, Warning, TEXT("pawn ok"));
//    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
//    RobotHUDWidget = CreateWidget<URobotHUDWidget>(this, GameInstance->DefaultAssetsBP->RobotHUDWidgetBP);
//    RobotHUDWidget->SetRobotCharacter(Cast<ARobotCharacter>(GetPawn()));
//    RobotHUDWidget->AddToViewport();
//  }
//  else
//  {
//    UE_LOG(LogTemp, Warning, TEXT("pawn null"));
//  }
//}
//
