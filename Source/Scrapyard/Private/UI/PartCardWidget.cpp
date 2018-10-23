// Fill out your copyright notice in the Description page of Project Settings.

#include "PartCardWidget.h"
#include "Parts/RobotPart.h"
#include "Components/TextBlock.h"

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
  AddStatsText();
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

void UPartCardWidget::AddStatsText()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::AddStatsText"), *GetName());
  TArray<FStatText> StatsText = RobotPart->GetStatsText();
  for (int32 i = 0; i < StatsText.Num(); ++i)
  {
    UTextBlock* StatName = CreateWidget<UTextBlock>(GetOwningPlayer(), UTextBlock::StaticClass()); 
    UTextBlock* StatValue = CreateWidget<UTextBlock>(GetOwningPlayer(), UTextBlock::StaticClass()); 
    StatName->SetText(FText::FromString(StatsText[0].StatName));
    StatValue->SetText(FText::FromString(StatsText[0].StatValue));
    StatsBox->AddChild(StatName);
    StatsBox->AddChild(StatValue);
  }

      
}
