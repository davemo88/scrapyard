// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPlayerController.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotPlayerCameraManager.h"

ARobotPlayerController::ARobotPlayerController()
{
  UE_LOG(LogTemp, Warning, TEXT("ARobotPlayerController Constructor"));
  PlayerCameraManagerClass = ARobotPlayerCameraManager::StaticClass();
}

void ARobotPlayerController::Possess(APawn* InPawn)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::Possess"), *GetName());

  Super::Possess(InPawn);
//  RobotCharacter = Cast<ARobotCharacter>(GetPawn());
}

void ARobotPlayerController::SetupInputComponent()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetupInputComponent"), *GetName());
  Super::SetupInputComponent();

  RobotCharacter = Cast<ARobotCharacter>(GetPawn());
  if (GetPawn() == NULL)
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::SetupInputComponent, Pawn is null"), *GetName());
  }

  if (RobotCharacter != NULL)
  {
// gamepad controls
    UE_LOG(LogTemp, Warning, TEXT("Binding Inputs"));
    InputComponent->BindAxis("MoveX", RobotCharacter, &ARobotCharacter::Axis_MoveX);
    InputComponent->BindAxis("MoveY", RobotCharacter, &ARobotCharacter::Axis_MoveY);

    InputComponent->BindAxis("TurnZ", RobotCharacter, &APawn::AddControllerYawInput);
    InputComponent->BindAxis("TurnY", RobotCharacter, &APawn::AddControllerPitchInput);
  
    InputComponent->BindAxis("Boost", RobotCharacter, &ARobotCharacter::Axis_Boost);
  
    InputComponent->BindAction("Jump", IE_Pressed, RobotCharacter, &ARobotCharacter::Jump);
  
    InputComponent->BindAction("PrimaryFire", IE_Pressed, this, &ARobotPlayerController::OnFire);
    InputComponent->BindAction("PrimaryFire", IE_Released, this, &ARobotPlayerController::OnStopFire);
    
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Can't bind input: RobotCharacter is NULL :("));
  }
}

void ARobotPlayerController::ClientSetupInputComponent_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ClientSetupInputComponent"), *GetName());
  SetupInputComponent();
}

void ARobotPlayerController::OnFire()
{
  UE_LOG(LogTemp, Warning, TEXT("ARobotPlayerController::OnFire"));
  bFirePressed = true;
  if (GetPawn() != NULL)
  {
    new(DeferredFireInputs)FDeferredFireInput(0, true);
  }
}

void ARobotPlayerController::OnStopFire()
{
  UE_LOG(LogTemp, Warning, TEXT("ARobotPlayerController::StopFire"));
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
