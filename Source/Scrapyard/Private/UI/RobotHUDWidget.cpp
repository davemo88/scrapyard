// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Robots/RobotCharacter.h"
#include "Components/TextBlock.h"

void URobotHUDWidget::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
  Super::NativeTick(MyGeometry, InDeltaTime);
// widgets don't tick when they aren't shown
// so can avoid this null check if this widget can't be shown without RobotCharacter being set
// maybe override its add to viewport method to check first?
//  if (RobotCharacter != NULL)
//  {
//// TODO: can do this manually whenever actually using power
//    UpdatePowerBar(); 
//  }
}

void URobotHUDWidget::SetRobotCharacter(ARobotCharacter* NewRobotCharacter)
{
  RobotCharacter = NewRobotCharacter;
  UpdateHitPoints();
  UpdatePowerBar();
  RobotCharacter->HitPointsChangedDelegate.AddDynamic(this, &URobotHUDWidget::UpdateHitPoints);
  RobotCharacter->PowerChangedDelegate.AddDynamic(this, &URobotHUDWidget::UpdatePowerBar);
}

void URobotHUDWidget::UpdatePowerBar()
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::UpdatePowerBar"), *GetName());
  PowerText->SetText(FText::AsNumber(RobotCharacter->Power));
  PowerBar->SetPercent((float)RobotCharacter->Power / (float)RobotCharacter->RobotStats->MaxPower);
}

void URobotHUDWidget::UpdateHitPoints()
{
  HitPointsText->SetText(FText::AsNumber(RobotCharacter->HitPoints));
}

//
//void URobotHUDWidget::SetHitPointsText(FText NewHitPointsText)
//{
//  HitPointsText->SetText(NewHitPointsText);
//}

