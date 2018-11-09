// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Robots/RobotCharacter.h"

void URobotHUDWidget::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
  Super::NativeTick(MyGeometry, InDeltaTime);
// widgets don't tick when they aren't shown
// so can avoid this null check if this widget can't be shown without RobotCharacter being set
// maybe override its add to viewport method to check first?
  if (RobotCharacter != NULL)
  {
    UpdatePowerBar(); 
  }
}

void URobotHUDWidget::SetRobotCharacter(ARobotCharacter* NewRobotCharacter)
{
  RobotCharacter = NewRobotCharacter;
  SetHitPointsText(FText::AsNumber(RobotCharacter->HitPoints));
}

void URobotHUDWidget::UpdatePowerBar()
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::UpdatePowerBar"), *GetName());
  PowerText->SetText(FText::AsNumber(RobotCharacter->Power));
  PowerBar->SetPercent((float)RobotCharacter->Power / (float)RobotCharacter->RobotStats->MaxPower);
}

void URobotHUDWidget::SetHitPointsText(FText NewHitPointsText)
{
  HitPointsText->SetText(NewHitPointsText);
}

