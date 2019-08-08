// Fill out your copyright notice in the Description page of Project Settings.


#include "YourPartsWidget.h"
#include "UI/PartCardWidget.h"
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

void UYourPartsWidget::AddDisplayedPart(URobotPart* RobotPart)
{
  UE_LOG(LogUI, Verbose, TEXT("%s::AddDisplayedPart"), *GetName());
  UE_LOG(LogUI, VeryVerbose, TEXT("%s::AddDisplayedPart - %s"), *GetName(), *RobotPart->PartName.ToString());

// don't display cards that are currently assigned to the robot
// or default parts
  if (!RobotPart->IsAssignedTo(CurrentDraft->PartAssignment) && !RobotPart->IsDefaultPart())
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetWorld()->GetGameInstance());
//    UCardWidgetBase* Card = CreateWidget<UCardWidgetBase>(GetOwningPlayer(), GameInstance->AssetsBP->UIAssetsBP->CardWidgetBaseBP); 
    UPartCardWidget* Card = CreateWidget<UPartCardWidget>(GetOwningPlayer(), GameInstance->AssetsBP->UIAssetsBP->PartCardWidgetBP); 
    Card->bCanBeDragged = true;
    Card->CardDroppedDelegate.AddDynamic(this, &UYourPartsWidget::ReorderCards);
    Card->SetRobotPart(RobotPart);
    DisplayedCards->AddChild(Card);
    Card->CardSizeBox->SetWidthOverride(200);
    NewCardAddedDelegate.Broadcast(Card);
  }
}

void UYourPartsWidget::ReorderCards(UCardWidgetBase* DroppedOnCard, UDragDropOperation* DragDropOp)
{
  UE_LOG(LogUI, Log, TEXT("%s::ReorderCards"), *GetName());
  if (UCardWidgetBase* DroppedCard = Cast<UCardWidgetBase>(DragDropOp->DefaultDragVisual))
  {
    if (DisplayedCards->HasChild(DroppedCard) && DisplayedCards->HasChild(DroppedOnCard))
    { 
      int32 DroppedIndex = DisplayedCards->GetChildIndex(DroppedCard);
      int32 DroppedOnIndex = DisplayedCards->GetChildIndex(DroppedOnCard);
      UE_LOG(LogUI, Log, TEXT("%s::ReorderCards - %i dropped on %i"), *GetName(), DroppedIndex, DroppedOnIndex);
      TArray<UWidget*> CurrentOrder = DisplayedCards->GetAllChildren();
      CurrentOrder.RemoveAt(DroppedIndex);
      CurrentOrder.Insert(DroppedCard, DroppedOnIndex);
      ClearDisplayedCards();
      for (UWidget* Card : CurrentOrder)
      {
        DisplayedCards->AddChild(Card);
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

