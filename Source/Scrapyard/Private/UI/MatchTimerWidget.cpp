// Fill out your copyright notice in the Description page of Project Settings.


#include "MatchTimerWidget.h"
#include "Game/RobotGameState.h"

void UMatchTimerWidget::StartMatchTimer()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::StartMatchTimer"), *GetName());
  SetVisibility(ESlateVisibility::Visible);
  UpdateMatchTimer();
}

void UMatchTimerWidget::StopMatchTimer()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::StopMatchTimer"), *GetName());
  SetVisibility(ESlateVisibility::Hidden);
}

void UMatchTimerWidget::UpdateMatchTimer()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::UpdateMatchTimer"), *GetName());
//TODO: refactor this 
  if (ARobotGameState* RobotGS = Cast<ARobotGameState>(GetWorld()->GetGameState()))
  {
    MatchTime->SetText(FText::AsNumber(RobotGS->GetMatchTimerSecondsRemaining()));
  }
}



