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

bool ARobotPlayerController::ServerSetPartAssignment_Validate(FPartAssignmentIDs NewPartAssignmentIDs)
{
  return true;
}

void ARobotPlayerController::ServerSetPartAssignment_Implementation(FPartAssignmentIDs NewPartAssignmentIDs)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ServerSetPartAssignment_Implementation"), *GetName());
  PartAssignmentIDs = NewPartAssignmentIDs;
  UE_LOG(LogTemp, Warning, TEXT("Head PartID: %d"), PartAssignmentIDs.HeadID);
  UE_LOG(LogTemp, Warning, TEXT("Core PartID: %d"), PartAssignmentIDs.CoreID);
  UE_LOG(LogTemp, Warning, TEXT("Arms PartID: %d"), PartAssignmentIDs.ArmsID);
  UE_LOG(LogTemp, Warning, TEXT("Legs PartID: %d"), PartAssignmentIDs.LegsID);

}

void ARobotPlayerController::ClientGetPartAssignment_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ClientGetPartAssignment_Implementation"), *GetName());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  if (GameInstance->PartAssignment != NULL)
  {
    ServerSetPartAssignment(GameInstance->PartAssignment->GetPartAssignmentIDs());
  }
}
