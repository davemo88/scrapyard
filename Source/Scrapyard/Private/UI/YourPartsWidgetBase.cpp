// Fill out your copyright notice in the Description page of Project Settings.


#include "YourPartsWidgetBase.h"
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
  ClearDisplayedCards();
  CurrentDraft = NewDraft;
  DisplayAll();
}

void UYourPartsWidgetBase::DisplayAll()
{
  TArray<URobotPart*> AllParts;
  AllParts.Append(CurrentDraft->DraftedHeads);
  AllParts.Append(CurrentDraft->DraftedCores);
  AllParts.Append(CurrentDraft->DraftedArms);
  AllParts.Append(CurrentDraft->DraftedLegs);
  AllParts.Append(CurrentDraft->DraftedBoosters);
  AllParts.Append(CurrentDraft->DraftedHandhelds);
  AllParts.Append(CurrentDraft->DraftedChips);

  DisplayParts(AllParts);
//  SortByType();
}

void UYourPartsWidgetBase::ClearDisplayedCards()
{
  DisplayedCards->ClearChildren();
}

void UYourPartsWidgetBase::RemoveDisplayedCard(UCardWidgetBase* Card)
{
//  DisplayedCards->RemoveChild(Card);
  Card->RemoveFromParent();
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

void UYourPartsWidgetBase::DisplayParts(TArray<URobotPart*> Parts)
{
  ClearDisplayedCards(); 
  for (URobotPart* Part : Parts)
  {
    AddDisplayedPart(Part);
  }
}


