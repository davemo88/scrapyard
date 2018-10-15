// Fill out your copyright notice in the Description page of Project Settings.


#include "YourPartsWidget.h"
#include "UI/PartCardWidget.h"
#include "SoloDraft.h"
#include "Game/SoloDraftGameState.h"

void UYourPartsWidget::ClearDisplayedCards()
{
  DisplayedCards->ClearChildren();
}

void UYourPartsWidget::AddDisplayedCard(UPartCardWidget* Card)
{
  DisplayedCards->AddChild(Card);
}

void UYourPartsWidget::FilterDisplayedCards(TSubclassOf<URobotPart> RobotPartClass)
{
   
}

void UYourPartsWidget::OnHeadFilterButtonClicked()
{
  ClearDisplayedCards(); 
  ASoloDraftGameState* GameState = GetWorld()->GetGameState<ASoloDraftGameState>();
  TArray<UHeadPart*> DraftedHeads = GameState->CurrentDraft->DraftedHeads;
  for (int32 i=0; i < DraftedHeads.Num(); ++i)
  {
  //  AddDisplayedCard(DraftedHeads[i]);
  }
}
