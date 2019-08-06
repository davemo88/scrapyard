// Fill out your copyright notice in the Description page of Project Settings.


#include "YourPartsWidget.h"
#include "Scrapyard.h"
#include "UI/PartCardWidget.h"
#include "UI/PartCardDragDropOperation.h"
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


void UYourPartsWidget::NativeConstruct()
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();

} 

bool UYourPartsWidget::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnDrop"), *GetName());
  if (UPartCardWidget* PartCard = Cast<UPartCardWidget>(InOperation->DefaultDragVisual))
  {
    UE_LOG(LogUI, Log, TEXT("Part Card Dropped: %s"), *PartCard->RobotPart->PartName.ToString());
    PartCardDroppedDelegate.Broadcast(PartCard);  
  }
  return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UYourPartsWidget::ReorderCards(UPartCardWidget* DroppedOnCard, UDragDropOperation* DragDropOp)
{
  UE_LOG(LogUI, Log, TEXT("%s::ReorderCards"), *GetName());
  if (UPartCardWidget* DroppedCard = Cast<UPartCardWidget>(DragDropOp->DefaultDragVisual))
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

void UYourPartsWidget::ClearDisplayedCards()
{
  DisplayedCards->ClearChildren();
}

void UYourPartsWidget::AddDisplayedCard(UPartCardWidget* Card)
{
  DisplayedCards->AddChild(Card);
  Card->CardSizeBox->SetWidthOverride(200);
//  Card->CardSizeBox->SetHeightOverride(258);
}

void UYourPartsWidget::RemoveDisplayedCard(UPartCardWidget* Card)
{
  DisplayedCards->RemoveChild(Card);
}

void UYourPartsWidget::AddDisplayedPart(URobotPart* RobotPart)
{
  UE_LOG(LogUI, Verbose, TEXT("%s::AddDisplayedPart"), *GetName());
  UE_LOG(LogUI, VeryVerbose, TEXT("%s::AddDisplayedPart - %s"), *GetName(), *RobotPart->PartName.ToString());

// don't display cards that are currently assigned to the robot
// or default parts
  if (!RobotPart->IsAssignedTo(CurrentDraft->PartAssignment) && !RobotPart->IsDefaultPart())
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetWorld()->GetGameInstance());
    UPartCardWidget* Card = CreateWidget<UPartCardWidget>(GetOwningPlayer(), GameInstance->AssetsBP->UIAssetsBP->PartCardWidgetBP); 
    Card->bCanBeDragged = true;
    Card->CardDroppedDelegate.AddDynamic(this, &UYourPartsWidget::ReorderCards);
    Card->SetRobotPart(RobotPart);
    AddDisplayedCard(Card);
    NewPartCardAdded.Broadcast(Card);
  }

}

void UYourPartsWidget::DisplayParts(TArray<URobotPart*> Parts)
{
  ClearDisplayedCards(); 
  for (int32 i=0; i<Parts.Num(); ++i)
  {
    AddDisplayedPart(Parts[i]);
  }
}

void UYourPartsWidget::DisplayAll()
{
  DisplayParts(CurrentDraft->DraftedParts);
//  SortByType();
}

void UYourPartsWidget::OnSortButtonClicked()
{

}

void UYourPartsWidget::SortByUserOrder()
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

  auto NewOrder = TArray<URobotPart*>(CurrentDraft->DraftedParts);

  Algo::Sort(NewOrder, [TypeOrder](URobotPart* Part1, URobotPart* Part2)
      { return TypeOrder.Find(Part1->GetClass()) < TypeOrder.Find(Part2->GetClass()); });
   
  DisplayParts(NewOrder);  

}

void UYourPartsWidget::SortByColor()
{

}

