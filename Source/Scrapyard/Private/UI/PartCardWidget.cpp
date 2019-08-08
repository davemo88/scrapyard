// Fill out your copyright notice in the Description page of Project Settings.

#include "PartCardWidget.h"
#include "Scrapyard.h"
#include "Parts/RobotPart.h"
#include "UI/StatLineWidget.h"
#include "Game/ScrapyardAssets.h"
#include "Game/ScrapyardGameInstance.h"
#include "Components/VerticalBox.h"
#include "Animation/UMGSequencePlayer.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/PartCardDragDropOperation.h"

void UPartCardWidget::SetRobotPart(URobotPart* NewRobotPart)
{
  Super::SetRobotPart(NewRobotPart);
  if (RobotPart->Manufacturer->Card)
  {
    CardBackground->SetBrushFromTexture(RobotPart->Manufacturer->Card);
  }
  AddStatsText();
}

void UPartCardWidget::NativeOnDragDetected(const FGeometry & InGeometry, const FPointerEvent & InDragDropEvent, UDragDropOperation *& OutOperation)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnDragDetected"), *GetName());
  Super::NativeOnDragDetected(InGeometry, InDragDropEvent, OutOperation);
  OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UPartCardDragDropOperation::StaticClass());
  OutOperation->DefaultDragVisual = this;
  CardDraggedDelegate.Broadcast(this);
}

bool UPartCardWidget::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnDrop"), *GetName());
  CardDroppedDelegate.Broadcast(this,InOperation);
  return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UPartCardWidget::AddStatsText()
{
  UE_LOG(LogUI, VeryVerbose, TEXT("%s::AddStatsText"), *GetName());
  TArray<FStatText> StatsText = RobotPart->GetStatsText();
  for (int32 i = 0; i < StatsText.Num(); ++i)
  {
    AddStatLine(StatsText[i]); 
  }
}

void UPartCardWidget::AddStatLine(FStatText StatText)
{
  UE_LOG(LogUI, VeryVerbose, TEXT("%s::AddStatLine"), *GetName());
  APlayerController* OwningPlayer = GetOwningPlayer();
  UScrapyardGameInstance* GameInstance = OwningPlayer->GetWorld()->GetGameInstance<UScrapyardGameInstance>();
  UStatLineWidget* StatLine = CreateWidget<UStatLineWidget>(OwningPlayer, GameInstance->AssetsBP->UIAssetsBP->StatLineWidgetBP);
  StatLine->SetStatLine(StatText);
  StatsBox->AddChild(StatLine);

}

UUMGSequencePlayer* UPartCardWidget::PlayFadeOut()
{
  return PlayAnimation(FadeOut);
}

void UPartCardWidget::OnFadeOutFinished(UUMGSequencePlayer & UUMGSequencePlayer)
{
  UE_LOG(LogUI, Log, TEXT("%s::OnFadeOutFinished"), *GetName());
  FadeOutFinishedDelegate.Broadcast(this); 
}
