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
  UE_LOG(LogUI, Log, TEXT("%s::OnPartCardClicked"), *GetName());
  CardClickedDelegate.Broadcast(RobotPart);
}

FReply UPartCardWidget::NativeOnMouseButtonDoubleClick(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnMouseButtonDoubleClick"), *GetName());
  CardDoubleClickedDelegate.Broadcast(RobotPart);
  return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}

void UPartCardWidget::NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Verbose, TEXT("%s::NativeOnMouseEnter"), *GetName());
  CardMouseEnteredDelegate.Broadcast(RobotPart);
  if (bHoverBorderActive)
  {
//    UE_LOG(LogTemp, Warning, TEXT("Playing Show Hover Border"), *GetName());
    PlayAnimation(ShowHoverBorder);
  }
  Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UPartCardWidget::NativeOnMouseLeave(const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Verbose, TEXT("%s::NativeOnMouseLeave"), *GetName());
  CardMouseLeftDelegate.Broadcast(RobotPart);
  if (bHoverBorderActive)
  {
    PlayAnimation(HideHoverBorder);
//    HoverBorder->SetVisibility(ESlateVisibility::Hidden);
  }
  Super::NativeOnMouseLeave(InMouseEvent);
}

FReply UPartCardWidget::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Verbose, TEXT("%s::NativeOnMouseButtonDown"), *GetName());
// stops OnMouseLeave event from firing by not calling Super
  return FReply::Handled();
}

FReply UPartCardWidget::NativeOnMouseButtonUp(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Verbose, TEXT("%s::NativeOnMouseButtonUp"), *GetName());
// stops OnMouseEnter event from firing by not calling Super
  CardClickedDelegate.Broadcast(RobotPart);
  return FReply::Handled();
}

//FReply UPartCardWidget::NativeOnMouseLeave(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
//{
//
//}

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
