// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftWidget.h"
#include "Scrapyard.h"
#include "SoloDraftPlayerController.h"
#include "UI/YourPartsWidget.h"
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

  UpdatePickCounter();
}

void USoloDraftWidget::UpdatePickCounter()
{
  ASoloDraftGameState* GameState = GetWorld()->GetGameState<ASoloDraftGameState>();
  FString PickCounterText = FString::Printf(TEXT("(%i of %i)"), GameState->CurrentDraft->NumPicks, GameState->CurrentDraft->MaxPicks);
  PickCounter->SetText(FText::FromString(PickCounterText));
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
    Card->CardMouseEnteredDelegate.AddDynamic(OwningController, &ASoloDraftPlayerController::OnPartCardHovered);
    Card->CardClickedDelegate.AddDynamic(OwningController, &ASoloDraftPlayerController::OnPartDrafted);
//TODO: render scale or make a bigger version
    Card->CardSizeBox->SetWidthOverride(360);
    Card->CardSizeBox->SetHeightOverride(495);
    Card->bHoverBorderActive = true;
//    Card->SetRenderScale(FVector2D(1.5,1.5));
    PackDisplayPanel->AddChild(Card);
    if (UUniformGridSlot* Slot = Cast<UUniformGridSlot>(Card->Slot))
    {
      Slot->SetColumn(i);
      Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
    }
  }
}

void USoloDraftWidget::OnCardFadedOut(UPartCardWidget* PartCardWidget)
{
  PartCardWidget->RemoveFromParent();
  if (PackDisplayPanel->GetAllChildren().Num() == 0)
  {
    DisplayNextPack();
  }
}
