// Fill out your copyright notice in the Description page of Project Settings.


#include "YourPartsWidgetBase.h"
#include "UI/CardWidgetBase.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/BoosterPart.h"
#include "Parts/HandheldPart.h"
#include "Parts/ChipPart.h"

void UYourPartsWidgetBase::SetCurrentDraft(UDraftBase* NewDraft)
{
  CurrentDraft = NewDraft;
}

void UYourPartsWidgetBase::DisplayPart(URobotPart* RobotPart)
{
  UE_LOG(LogUI, Verbose, TEXT("%s::DisplayPart"), *GetName());
  UE_LOG(LogUI, VeryVerbose, TEXT("%s::DisplayPart - %s"), *GetName(), *RobotPart->PartName.ToString());
  DisplayedParts.Add(RobotPart);
  RefreshDisplayedCards();
}

void UYourPartsWidgetBase::DisplayParts(TArray<URobotPart*> NewDisplayedParts)
{
  DisplayedParts = NewDisplayedParts;
  RefreshDisplayedCards();
}

void UYourPartsWidgetBase::DisplayUnassignedParts()
{
  TArray<URobotPart*> UnassignedParts;
  if (CurrentDraft != nullptr)
  {
    UnassignedParts = CurrentDraft->GetAllDraftedParts().FilterByPredicate([this](URobotPart* Part) { return !Part->IsAssignedTo(CurrentDraft->PartAssignment); }); 
  }
  DisplayParts(UnassignedParts);
}

void UYourPartsWidgetBase::RemoveDisplayedCard(UCardWidgetBase* Card)
{
  DisplayedParts.Remove(Card->RobotPart);
// BUG: sometimes this not getting removed from parent?
// oh this is because it's not removing the one from the yourpartswidget, just the installed part widget ?
  Card->RemoveFromParent();
  RefreshDisplayedCards();
}

bool UYourPartsWidgetBase::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnDrop"), *GetName());
  if (UCardWidgetBase* PartCard = Cast<UCardWidgetBase>(InOperation->DefaultDragVisual))
  {
    UE_LOG(LogUI, Log, TEXT("Part Card Dropped: %s"), *PartCard->RobotPart->PartName.ToString());
    CardDroppedInYourPartsDelegate.Broadcast(PartCard);  
  }
  return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

UCardWidgetBase* UYourPartsWidgetBase::GetCardWidget()
{
  return nullptr;
}

void UYourPartsWidgetBase::SortDisplayedParts()
{
  Algo::Sort(DisplayedParts, [](URobotPart* Part1, URobotPart* Part2)
    { 
      if (Part1->PartType == Part2->PartType)
      {
        return Part1->PartName.ToString() < Part2->PartName.ToString();
      }
      return Part1->PartType < Part2->PartType;
    });
}

void UYourPartsWidgetBase::RefreshDisplayedCards()
{
  UE_LOG(LogUI, Log, TEXT("%s::RefreshDisplayedCards"), *GetName());
  CardDisplayPanel->ClearChildren();
  SortDisplayedParts();
  for (URobotPart* Part : DisplayedParts)
  {
    UCardWidgetBase* Card = GetCardWidget();
    Card->bCanBeDragged = true;
    Card->SetRobotPart(Part);
    CardDisplayPanel->AddChild(Card);
    NewCardAddedDelegate.Broadcast(Card);
  }
}
