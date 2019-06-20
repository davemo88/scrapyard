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
  NewValueText->SetText(FText());
}

void URobotStatLineWidget::SetNewValue(int32 NewValue, int32 OldValue, FBetterComparator IsBetter)
{
  if (NewValue != OldValue)
  {
    NewValueText->SetText(FText::AsNumber(NewValue));
    NewValueArrow->SetVisibility(ESlateVisibility::Visible);
    if (IsBetter(NewValue, OldValue))
    {
      NewValueText->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
    }
    else
    {
      NewValueText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
    }
  }
  else
  {
    NewValueText->SetText(FText());
    NewValueArrow->SetVisibility(ESlateVisibility::Hidden);
  }
}


