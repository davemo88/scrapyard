// Fill out your copyright notice in the Description page of Project Settings.


#include "YourPartsWidget.h"
#include "UI/PartCardWidget.h"

void UYourPartsWidget::ClearDisplayedCards()
{
  DisplayedCards->ClearChildren();
}

void UYourPartsWidget::AddDisplayedCard(UPartCardWidget* Card)
{
  DisplayedCards->AddChild(Card);
}

