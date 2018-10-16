// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftWidget.h"
#include "SoloDraftPlayerController.h"
#include "UI/YourPartsWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Game/SoloDraftGameState.h"

void USoloDraftWidget::NativeConstruct()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();

  UpdatePickCounter();
}

void USoloDraftWidget::UpdatePickCounter()
{
  ASoloDraftGameState* GameState = GetWorld()->GetGameState<ASoloDraftGameState>();
  FString PickCounterText = FString::Printf(TEXT("%i/%i"), GameState->CurrentDraft->Picks, GameState->CurrentDraft->MaxPicks);
  PickCounter->SetText(FText::FromString(PickCounterText));
}

void USoloDraftWidget::DisplayNextPack()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::DisplayNextPack"), *GetName());
  ASoloDraftPlayerController* OwningController = Cast<ASoloDraftPlayerController>(GetOwningPlayer());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  ASoloDraftGameState* GameState = GetWorld()->GetGameState<ASoloDraftGameState>();

  PackDisplayPanel->ClearChildren();

  TArray<URobotPart*> NextPack = GameState->CurrentDraft->CurrentPack;

  for (int32 i = 0; i < NextPack.Num(); ++i)
  {
    UPartCardWidget* Card = CreateWidget<UPartCardWidget>(OwningController, GameInstance->DefaultAssetsBP->PartCardWidgetBP); 
    Card->SetRobotPart(NextPack[i]);
    Card->CardMouseEnteredDelegate.AddDynamic(OwningController, &ASoloDraftPlayerController::OnPartCardHovered);
    Card->CardDoubleClickedDelegate.AddDynamic(OwningController, &ASoloDraftPlayerController::OnPartDoubleClicked);
    PackDisplayPanel->AddChild(Card);
    if (UUniformGridSlot* Slot = Cast<UUniformGridSlot>(Card->Slot))
    {
      Slot->SetColumn(i);
    }
  }
}
