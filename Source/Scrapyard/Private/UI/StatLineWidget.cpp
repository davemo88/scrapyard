// Fill out your copyright notice in the Description page of Project Settings.


#include "StatLineWidget.h"
#include "Components/TextBlock.h"

void UStatLineWidget::SetStatLine(FStatText StatText)
{
  StatName->SetText(StatText.StatName);
  StatValue->SetText(StatText.StatValue);
}

