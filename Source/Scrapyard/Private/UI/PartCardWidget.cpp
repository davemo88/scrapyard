// Fill out your copyright notice in the Description page of Project Settings.

#include "PartCardWidget.h"
#include "Parts/RobotPart.h"
#include "UI/StatLineWidget.h"
#include "Game/ScrapyardAssets.h"
#include "Game/ScrapyardGameInstance.h"
#include "Components/VerticalBox.h"
#include "Blueprint/WidgetTree.h"

void UPartCardWidget::SetRobotPart(URobotPart* NewRobotPart)
{
  RobotPart = NewRobotPart;
// NOTE: being reckless here
  if (RobotPart->Manufacturer->Card)
  {
    CardBackground->SetBrushFromTexture(RobotPart->Manufacturer->Card);
  }
  if (UTexture2D* CardIcon = RobotPart->GetPartTypeIcon())
  {
    PartTypeIcon->SetBrushFromTexture(CardIcon); 
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
    AddStatLine(StatsText[i]); 
  }
}

void UPartCardWidget::AddStatLine(FStatText StatText)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::AddStatLine"), *GetName());
  APlayerController* OwningPlayer = GetOwningPlayer();
  UScrapyardGameInstance* GameInstance = OwningPlayer->GetWorld()->GetGameInstance<UScrapyardGameInstance>();
  UStatLineWidget* StatLine = CreateWidget<UStatLineWidget>(OwningPlayer, GameInstance->AssetsBP->UIAssetsBP->StatLineWidgetBP);
  StatLine->SetStatLine(StatText);
  StatsBox->AddChild(StatLine);

}
