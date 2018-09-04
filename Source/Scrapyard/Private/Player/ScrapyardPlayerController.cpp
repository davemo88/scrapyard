// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardPlayerController.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "Robots/RobotCharacter.h"
#include "UI/RobotHUDWidget.h"

void AScrapyardPlayerController::BeginPlay()
{
  Super::BeginPlay();

  SetupRobotHUDWidget();
}

void AScrapyardPlayerController::SetupRobotHUDWidget()
{
  if (GetPawn())
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
    RobotHUDWidget = CreateWidget<URobotHUDWidget>(this, GameInstance->DefaultAssetsBP->RobotHUDWidgetBP);
    RobotHUDWidget->SetRobotCharacter(Cast<ARobotCharacter>(GetPawn()));
    RobotHUDWidget->AddToViewport();
  }
}

void AScrapyardPlayerController::OnFire()
{
  bFirePressed = true;
  if (GetPawn() != NULL)
  {
    new(DeferredFireInputs)FDeferredFireInput(0, true);
  }
}

bool AScrapyardPlayerController::HasDeferredFireInputs()
{
  for (FDeferredFireInput& Input : DeferredFireInputs)
  {
    if (Input.bStartFire)
    {
      return true;
    }
  }
  return false;
}

void AScrapyardPlayerController::ApplyDeferredFireInputs()
{
  for (FDeferredFireInput Input : DeferredFireInputs)
  {
    if (Input.bStartFire)
    {
      if (!IsMoveInputIgnored())
      {
        if(RobotCharacter != NULL)
        {
          RobotCharacter->StartFire(Input.FireMode);
        }
      }
    }
// stop fire
    else if (RobotCharacter != NULL)
    {
      RobotCharacter->StopFire(Input.FireMode);
    }
  }
}
