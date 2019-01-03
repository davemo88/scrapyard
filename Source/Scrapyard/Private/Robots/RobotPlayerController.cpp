// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPlayerController.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotPlayerCameraManager.h"
#include "GameFramework/PlayerController.h"

ARobotPlayerController::ARobotPlayerController()
{
  UE_LOG(LogTemp, Warning, TEXT("ARobotPlayerController Constructor"));
  PlayerCameraManagerClass = ARobotPlayerCameraManager::StaticClass();
}

void ARobotPlayerController::BeginPlay()
{
  Super::BeginPlay();
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
//  UGameViewportClient* ViewportClient = GetWorld()->GetGameInstance()->GetGameViewportClient();
//  ViewportClient->Viewport->CaptureMouse(true);
//  ViewportClient->Viewport->SetUserFocus(true);
  const FInputModeGameOnly InputMode = FInputModeGameOnly();
  SetInputMode(InputMode);

}

void ARobotPlayerController::Possess(APawn* InPawn)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::Possess"), *GetName());

  Super::Possess(InPawn);
}

void ARobotPlayerController::OnFire()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnFire"), *GetName());
  bFirePressed = true;
  if (GetPawn() != NULL)
  {
    new(DeferredFireInputs)FDeferredFireInput(0, true);
  }
}

void ARobotPlayerController::OnStopFire()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::StopFire"), *GetName());
  bFirePressed = false;
  if (GetPawn() != NULL)
  {
    new(DeferredFireInputs)FDeferredFireInput(0, false);
  }
}

bool ARobotPlayerController::HasDeferredFireInputs()
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

void ARobotPlayerController::ApplyDeferredFireInputs()
{
//  UE_LOG(LogTemp,Warning,TEXT("ARobotPlayerController::ApplyDeferredFireInputs"));
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
  DeferredFireInputs.Empty();
}

void ARobotPlayerController::SetRobotCharacter(ARobotCharacter* NewRobotCharacter)
{
  RobotCharacter = NewRobotCharacter;
}
