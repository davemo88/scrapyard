// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCardWidget.h"
#include "Parts/RobotPart.h"

void UMiniCardWidget::SetRobotPart(URobotPart* NewRobotPart)
{
  Super::SetRobotPart(NewRobotPart);
  if (RobotPart->Manufacturer->MiniCard)
  {
    CardBackground->SetBrushFromTexture(RobotPart->Manufacturer->MiniCard);
  }
}


