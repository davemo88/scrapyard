// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardPlayerController.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "UI/EscapeMenuWidget.h"
#include "Robots/RobotCharacter.h"
#include "UI/RobotHUDWidget.h"
#include "GameFramework/PlayerController.h"

AScrapyardPlayerController::AScrapyardPlayerController()
{
  UE_LOG(LogTemp,Warning,TEXT("scrapyard constructor- bDefaultShowMouseCursor is %s"), (bDefaultShowMouseCursor ? TEXT("True") : TEXT("False")));
  bDefaultShowMouseCursor = false;
  bShowMouseCursor = bDefaultShowMouseCursor;
}

void AScrapyardPlayerController::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();

  if (IsLocalController())
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
    EscapeMenuWidget = CreateWidget<UEscapeMenuWidget>(this, GameInstance->DefaultAssetsBP->EscapeMenuWidgetBP);
    EscapeMenuWidget->SetVisibility(ESlateVisibility::Hidden);
//  TODO: this is hacky
    EscapeMenuWidget->AddToViewport(999);
  }
}

void AScrapyardPlayerController::SetupInputComponent()
{
  Super::SetupInputComponent();
  if (IsLocalController())
  {
    InputComponent->BindAction("Escape",IE_Pressed, this, &AScrapyardPlayerController::ToggleEscapeMenu);
  }
}

void AScrapyardPlayerController::ToggleEscapeMenu()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ToggleEscapeMenu"), *GetName());
  if (EscapeMenuWidget->IsVisible())
  {
    HideEscapeMenu();
  }
  else
  {
    ShowEscapeMenu();
  }
}

void AScrapyardPlayerController::ShowEscapeMenu()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ShowEscapeMenu"), *StaticClass()->GetFName().ToString());
  EscapeMenuWidget->SetVisibility(ESlateVisibility::Visible);
  ClientIgnoreLookInput(true);
  const FInputModeGameAndUI InputMode = FInputModeGameAndUI();
  SetInputMode(InputMode);
  bShowMouseCursor = true;
  EscapeMenuWidget->SetUserFocus(this);
}


void AScrapyardPlayerController::HideEscapeMenu()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::HideEscapeMenu"), *StaticClass()->GetFName().ToString());
  EscapeMenuWidget->SetVisibility(ESlateVisibility::Hidden);
  ClientIgnoreLookInput(false);
  const FInputModeGameOnly InputMode = FInputModeGameOnly();
  SetInputMode(InputMode);
  bShowMouseCursor = bDefaultShowMouseCursor;
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
