// Fill out your copyright notice in the Description page of Project Settings.


#include "YourPartsWidget.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/SoloDraftGameState.h"
#include "Game/ScrapyardAssets.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/BoosterPart.h"
#include "Parts/HandheldPart.h"
#include "Parts/ChipPart.h"
#include "UI/CardWidgetBase.h"
#include "UI/MiniCardWidget.h"

UCardWidgetBase* UYourPartsWidget::GetCardWidget()
{
  UPartCardWidget* Card = CreateWidget<UPartCardWidget>(GetOwningPlayer(), UScrapyardGameInstance::GameInstance->AssetsBP->UIAssetsBP->PartCardWidgetBP); 
  Card->CardSizeBox->SetWidthOverride(200);
  return Card;
}

void UYourPartsWidget::ReorderCards(UCardWidgetBase* DroppedOnCard, UDragDropOperation* DragDropOp)
{
  UE_LOG(LogUI, Log, TEXT("%s::ReorderCards"), *GetName());
  if (UCardWidgetBase* DroppedCard = Cast<UCardWidgetBase>(DragDropOp->DefaultDragVisual))
  {
    if (CardDisplayPanel->HasChild(DroppedCard) && CardDisplayPanel->HasChild(DroppedOnCard))
    { 
      int32 DroppedIndex = CardDisplayPanel->GetChildIndex(DroppedCard);
      int32 DroppedOnIndex = CardDisplayPanel->GetChildIndex(DroppedOnCard);
      UE_LOG(LogUI, Log, TEXT("%s::ReorderCards - %i dropped on %i"), *GetName(), DroppedIndex, DroppedOnIndex);
      TArray<UWidget*> CurrentOrder = CardDisplayPanel->GetAllChildren();
      CurrentOrder.RemoveAt(DroppedIndex);
      CurrentOrder.Insert(DroppedCard, DroppedOnIndex);
      CardDisplayPanel->ClearChildren();
      for (UWidget* Card : CurrentOrder)
      {
        CardDisplayPanel->AddChild(Card);
      }
    }
  }

}

void UYourPartsWidget::OnSortButtonClicked()
{

}

void UYourPartsWidget::SortByType()
{
  TArray<TSubclassOf<URobotPart>> TypeOrder;
  TypeOrder.Add(UHeadPart::StaticClass());
  TypeOrder.Add(UCorePart::StaticClass());
  TypeOrder.Add(UArmsPart::StaticClass());
  TypeOrder.Add(ULegsPart::StaticClass());
  TypeOrder.Add(UBoosterPart::StaticClass());
  TypeOrder.Add(UHandheldPart::StaticClass());
  TypeOrder.Add(UChipPart::StaticClass());

//  auto NewOrder = TArray<URobotPart*>(CurrentDraft->DraftedParts);
//
//  Algo::Sort(NewOrder, [TypeOrder](URobotPart* Part1, URobotPart* Part2)
//      { return TypeOrder.Find(Part1->GetClass()) < TypeOrder.Find(Part2->GetClass()); });
//   
//  DisplayParts(NewOrder);  

}

