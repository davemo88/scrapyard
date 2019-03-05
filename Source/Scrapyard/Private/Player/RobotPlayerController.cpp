// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPlayerController.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotPlayerCameraManager.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "Game/RobotGameState.h"
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
//TODO: why is this here?
  const FInputModeGameOnly InputMode = FInputModeGameOnly();
  SetInputMode(InputMode);

  SetupMatchTimerWidget();

}

void ARobotPlayerController::Possess(APawn* InPawn)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::Possess"), *GetName());
  Super::Possess(InPawn);

  if (ARobotCharacter* RoboChar = Cast<ARobotCharacter>(InPawn))
  {
    SetRobotCharacter(RoboChar);
//    RoboChar->RobotBodyComponent->PartAssignment->SetAssignment(PartAssignmentIDs);
    RoboChar->MulticastSetRobotPartAssignmentFromIDs(PartAssignmentIDs);
  }
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

void ARobotPlayerController::SetupMatchTimerWidget()
{
  if (IsLocalController())
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
    MatchTimerWidget = CreateWidget<UMatchTimerWidget>(this, GameInstance->DefaultAssetsBP->MatchTimerWidgetBP);
  //TODO: save pointer to gamestate?
    if (ARobotGameState* RobotGS = (Cast<ARobotGameState>(GetWorld()->GetGameState())))
    {
      RobotGS->OnMatchTimerStartedDelegate.AddDynamic(MatchTimerWidget, &UMatchTimerWidget::StartMatchTimer);
      RobotGS->OnMatchTimerUpdatedDelegate.AddDynamic(MatchTimerWidget, &UMatchTimerWidget::UpdateMatchTimer);
      RobotGS->OnMatchTimerStoppedDelegate.AddDynamic(MatchTimerWidget, &UMatchTimerWidget::StopMatchTimer);
    }
    MatchTimerWidget->SetVisibility(ESlateVisibility::Hidden);
    MatchTimerWidget->AddToViewport();
  }
}

bool ARobotPlayerController::ServerSetPartAssignmentIDs_Validate(FPartAssignmentIDs NewPartAssignmentIDs)
{
  return true;
}

void ARobotPlayerController::ServerSetPartAssignmentIDs_Implementation(FPartAssignmentIDs NewPartAssignmentIDs)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ServerSetPartAssignment_Implementation"), *GetName());
  PartAssignmentIDs = NewPartAssignmentIDs;
  UE_LOG(LogTemp, Warning, TEXT("Head PartID: %d"), PartAssignmentIDs.HeadID);
  UE_LOG(LogTemp, Warning, TEXT("Core PartID: %d"), PartAssignmentIDs.CoreID);
  UE_LOG(LogTemp, Warning, TEXT("Arms PartID: %d"), PartAssignmentIDs.ArmsID);
  UE_LOG(LogTemp, Warning, TEXT("Legs PartID: %d"), PartAssignmentIDs.LegsID);

}

void ARobotPlayerController::ClientGetPartAssignmentIDs_Implementation()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ClientGetPartAssignment_Implementation"), *GetName());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  if (GameInstance->PartAssignment != NULL)
  {
//TODO: replication or no?
    PartAssignmentIDs = GameInstance->PartAssignment->GetPartAssignmentIDs();
    ServerSetPartAssignmentIDs(PartAssignmentIDs);
  }
}

bool ARobotPlayerController::ServerNotifyGameStateReplicated_Validate()
{
  return true;
}

void ARobotPlayerController::ServerNotifyGameStateReplicated_Implementation()
{
  if (HasAuthority())
  {
    bGameStateReplicated = true;
  }
}

void ARobotCharacter::MulticastSetRobotPartAssignmentFromIDs_Implementation(FPartAssignmentIDs NewPartAssignmentIDs)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::MulticastSetRobotPartAssignmentFromIDs_Implementation"), *GetName());
  RobotBodyComponent->PartAssignment->SetAssignment(NewPartAssignmentIDs);
}

//void ARobotPlayerController::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
//{
//  Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//  DOREPLIFETIME(ARobotPlayerController, PartAssignmentIDs);
//}
//

void ARobotPlayerController::SetNewTune(FRobotTuneParams TuneParams)
{
  ApplyTuneParams(TuneParams);

  if (!HasAuthority())
  {
    ServerSetNewTune(TuneParams);
  }
}

void ARobotPlayerController::ServerSetNewTune_Implementation(FRobotTuneParams TuneParams)
{
  if (HasAuthority())
  {
    ApplyTuneParams(TuneParams);    
  }
}

bool ARobotPlayerController::ServerSetNewTune_Validate(FRobotTuneParams TuneParams)
{
  return true; 
}

void ARobotPlayerController::ApplyTuneParams(FRobotTuneParams TuneParams)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ApplyTuneParams"), *GetName());
  if (RobotCharacter)
  {
    if (URobotMovementComponent* RobotMovementComp = Cast<URobotMovementComponent>(RobotCharacter->GetMovementComponent()))
    {
      UE_LOG(LogTemp, Warning, TEXT("New GroundFriction: %s"), *TuneParams.GroundFriction);
      RobotMovementComp->GroundFriction = FCString::Atof(*TuneParams.GroundFriction);
      UE_LOG(LogTemp, Warning, TEXT("New BoostHoldThresholdTime: %s"), *TuneParams.BoostHoldThresholdTime);
      RobotMovementComp->BoostHoldThresholdTime= FCString::Atof(*TuneParams.BoostHoldThresholdTime);
    }
  }
}
