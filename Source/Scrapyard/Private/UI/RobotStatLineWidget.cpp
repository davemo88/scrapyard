// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotStatLineWidget.h"
#include "Components/TextBlock.h"

void URobotStatLineWidget::NativeConstruct()
{
  Super::NativeConstruct();
  NewValueArrow->SetVisibility(ESlateVisibility::Hidden);
}

void URobotStatLineWidget::SetStatLine(FStatText StatText)
{
  StatName->SetText(StatText.StatName);
  StatValue->SetText(StatText.StatValue);
  NewValue->SetText(FText());
}

void URobotStatLineWidget::SetNewValue(FText NewStatValue, bool bBetter)
{
  NewValue->SetText(NewStatValue);

  if (!NewStatValue.EqualTo(FText()))
  {
    NewValueArrow->SetVisibility(ESlateVisibility::Visible);
    if (bBetter)
    {
      NewValue->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
    }
    else
    {
      NewValue->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
    }
  }
  else
  {
    NewValueArrow->SetVisibility(ESlateVisibility::Hidden);
  }
}


