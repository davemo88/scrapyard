// Fill out your copyright notice in the Description page of Project Settings.

#include "PartCardWidget.h"
#include "Parts/RobotPart.h"
#include "Components/Image.h"

void UPartCardWidget::SetRobotPart(URobotPart* NewRobotPart)
{
  RobotPart = NewRobotPart;
  if (RobotPart->Manufacturer)
  {
    CardBackground->SetBrushColor(RobotPart->Manufacturer->CardBackgroundColor);
  }
  if (RobotPart->CardIcon)
  {
    PartTypeIcon->SetBrushFromTexture(RobotPart->CardIcon); 
  }
}

void UPartCardWidget::OnPartCardClicked()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnPartCardClicked"), *GetName());
  CardClickedDelegate.Broadcast(RobotPart);
}

FReply UPartCardWidget::NativeOnMouseButtonDoubleClick(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeOnMouseButtonDoubleClick"), *GetName());
  CardDoubleClickedDelegate.Broadcast(RobotPart);
  return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}

void UPartCardWidget::NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeOnMouseEnter"), *GetName());
  CardMouseEnteredDelegate.Broadcast(RobotPart);
  Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UPartCardWidget::NativeOnMouseLeave(const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeOnMouseLeave"), *GetName());
  Super::NativeOnMouseLeave(InMouseEvent);
}
