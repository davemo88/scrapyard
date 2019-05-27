// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardPlayerController.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
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
    EscapeMenuWidget = CreateWidget<UEscapeMenuWidget>(this, GameInstance->AssetsBP->UIAssetsBP->EscapeMenuWidgetBP);
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
  SetEscapeMenuInputMode();
  bShowMouseCursor = true;
//  EscapeMenuWidget->SetUserFocus(this);
}


void AScrapyardPlayerController::HideEscapeMenu()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::HideEscapeMenu"), *StaticClass()->GetFName().ToString());
  EscapeMenuWidget->SetVisibility(ESlateVisibility::Hidden);
  ClientIgnoreLookInput(false);
  SetDefaultInputMode();
  bShowMouseCursor = bDefaultShowMouseCursor;
}

void AScrapyardPlayerController::SetEscapeMenuInputMode()
{
//  const FInputModeGameAndUI InputMode = FInputModeGameAndUI();
//  const FInputModeUIOnly InputMode = FInputModeUIOnly();
  FInputModeGameAndUI InputMode = FInputModeGameAndUI();
  InputMode.SetWidgetToFocus(EscapeMenuWidget->TakeWidget());
//  InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
  SetInputMode(InputMode);
}

void AScrapyardPlayerController::SetDefaultInputMode()
{
  FInputModeGameAndUI InputMode = FInputModeGameAndUI();
  SetInputMode(InputMode);
}

