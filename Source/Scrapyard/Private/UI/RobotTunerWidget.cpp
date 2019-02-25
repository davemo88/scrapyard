// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotTunerWidget.h"



void URobotTunerWidget::NativeConstruct()
{
  Super::NativeConstruct();
}

void URobotTunerWidget::SetRobotChar(ARobotCharacter* NewRobotChar)
{
  RobotChar = NewRobotChar;
  RobotMovementComp = Cast<URobotMovementComponent>(RobotChar->GetMovementComponent());

  if (RobotMovementComp)
  {
    GroundFrictionTextBox->SetText(FText::AsNumber(RobotMovementComp->GroundFriction));
    BoostHoldThresholdTimeTextBox->SetText(FText::AsNumber(RobotMovementComp->BoostHoldThresholdTime));
  }

}

void URobotTunerWidget::SetNewTune()
{
//  ServerSetNewTune();
}

void URobotTunerWidget::ServerSetNewTune_Implementation()
{
//  RobotMovementComp->BoostHoldThresholdTime = NewValue; 
}

bool URobotTunerWidget::ServerSetNewTune_Validate()
{
  return true; 
}
