// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotTunerWidget.h"
#include "Player/RobotPlayerController.h"



void URobotTunerWidget::NativeConstruct()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();
  
  SetNewTuneButton->OnClicked.AddDynamic(this, &URobotTunerWidget::SetNewTune);

  if (APlayerController* PC = GetOwningPlayer())
  {
    SetRobotChar(Cast<ARobotCharacter>(PC->GetPawn()));
  }
}

void URobotTunerWidget::SetRobotChar(ARobotCharacter* NewRobotChar)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetRobotChar"), *GetName());
  if (NewRobotChar)
  {
    RobotChar = NewRobotChar;
    RobotMovementComp = Cast<URobotMovementComponent>(RobotChar->GetMovementComponent());
  }

  if (RobotMovementComp)
  {
    GroundFrictionTextBox->SetText(FText::AsNumber(RobotMovementComp->GroundFriction));
    BoostHoldThresholdTimeTextBox->SetText(FText::AsNumber(RobotMovementComp->BoostHoldThresholdTime));
  }

}

void URobotTunerWidget::SetNewTune()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetNewTune"), *GetName());
  FRobotTuneParams TuneParams = GetTuneParams();
  if (ARobotPlayerController* RobotPC = Cast<ARobotPlayerController>(GetOwningPlayer()))
  {
    RobotPC->SetNewTune(TuneParams);
  }

  SetVisibility(ESlateVisibility::Hidden);
}

FRobotTuneParams URobotTunerWidget::GetTuneParams()
{
  FRobotTuneParams TuneParams;

  TuneParams.GroundFriction = GroundFrictionTextBox->GetText().ToString();
  UE_LOG(LogTemp, Warning, TEXT("GetTuneParams GroundFriction: %s"), *TuneParams.GroundFriction);
  TuneParams.BoostHoldThresholdTime = BoostHoldThresholdTimeTextBox->GetText().ToString();
  UE_LOG(LogTemp, Warning, TEXT("GetTuneParams BoostHoldThresholdTime: %s"), *TuneParams.BoostHoldThresholdTime);

  return TuneParams;
}
