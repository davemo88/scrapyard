// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftWidget.h"
#include "Scrapyard.h"
#include "SoloDraftPlayerController.h"
#include "UI/YourPartsWidget.h"
#include "UI/PartCardWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Game/SoloDraftGameState.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Animation/UMGSequencePlayer.h"

void USoloDraftWidget::NativeConstruct()
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();

  YourPartsWidget->CardDroppedInYourPartsDelegate.AddDynamic(this, &USoloDraftWidget::OnCardDroppedInYourParts);
}

void USoloDraftWidget::NextPack()
{
  UE_LOG(LogUI, Verbose, TEXT("%s::NextPack"), *GetName());
  if (PackDisplayPanel->GetAllChildren().Num())
  {
    for (UWidget* Child : PackDisplayPanel->GetAllChildren())
    {
      if (UPartCardWidget* Card = Cast<UPartCardWidget>(Child))
      {
        Card->FadeOutFinishedDelegate.AddDynamic(this, &USoloDraftWidget::OnCardFadedOut);
// NOTE: the visibility is updated in the animation itself
//        Card->SetVisibility(ESlateVisibility::HitTestInvisible);
        Card->PlayFadeOut()->OnSequenceFinishedPlaying().AddUObject(Card, &UPartCardWidget::OnFadeOutFinished);
      }

    }
  }
  else
  {
    DisplayNextPack();
  }

}

void USoloDraftWidget::DisplayNextPack()
{
  UE_LOG(LogUI, Verbose, TEXT("%s::DisplayNextPack"), *GetName());
  ASoloDraftPlayerController* OwningController = Cast<ASoloDraftPlayerController>(GetOwningPlayer());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  ASoloDraftGameState* GameState = GetWorld()->GetGameState<ASoloDraftGameState>();
  
  TArray<URobotPart*> NextPack = GameState->CurrentDraft->CurrentPack;

  for (int32 i = 0; i < NextPack.Num(); ++i)
  {

    UPartCardWidget* Card = CreateWidget<UPartCardWidget>(OwningController, GameInstance->AssetsBP->UIAssetsBP->PartCardWidgetBP);

    Card->SetRobotPart(NextPack[i]);
    Card->CardClickedDelegate.AddDynamic(this, &USoloDraftWidget::OnCardDrafted);
    Card->CardDraggedDelegate.AddDynamic(this, &USoloDraftWidget::OnCardDragged);
    Card->bHoverBorderActive = true;
    Card->bCanBeDragged = true;
    PackDisplayPanel->AddChild(Card);
    if (UUniformGridSlot* Slot = Cast<UUniformGridSlot>(Card->Slot))
    {
      Slot->SetColumn(i);
      Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
    }
  }
  UpdatePickCounter();
}

void USoloDraftWidget::UpdatePickCounter()
{
  ASoloDraftGameState* GameState = GetWorld()->GetGameState<ASoloDraftGameState>();
  FString PickCounterText = FString::Printf(TEXT("(%i of %i)"), GameState->CurrentDraft->CurrentPick+1, GameState->CurrentDraft->TotalPicks);
  PickCounter->SetText(FText::FromString(PickCounterText));
}

void USoloDraftWidget::OnCardFadedOut(UPartCardWidget* PartCardWidget)
{
  PartCardWidget->RemoveFromParent();
//TODO: this could be a lot better
  if (PackDisplayPanel->GetAllChildren().Num() == 0)
  {
    DisplayNextPack();
  }
}

void USoloDraftWidget::OnCardDragged(UCardWidgetBase* CardWidget)
{
//  PartCardWidget->Slot
//  PartCardWidget->SetVisibility(ESlateVisibility::Hidden);
}

void USoloDraftWidget::OnCardDrafted(UCardWidgetBase* Card)
{
  PartDraftedDelegate.Broadcast(Card->RobotPart);
  YourPartsWidget->AddDisplayedPart(Card->RobotPart);
}

void USoloDraftWidget::OnCardDroppedInYourParts(UCardWidgetBase* Card)
{
  if (PackDisplayPanel->HasChild(Card))
  {
    OnCardDrafted(Card);
  }
}

void USoloDraftWidget::SetCurrentDraft(USoloDraft* NewDraft)
{
  CurrentDraft = NewDraft;

  YourPartsWidget->CurrentDraft = CurrentDraft;
}
