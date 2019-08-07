// Fill out your copyright notice in the Description page of Project Settings.


#include "YourPartsWidgetBase.h"


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



