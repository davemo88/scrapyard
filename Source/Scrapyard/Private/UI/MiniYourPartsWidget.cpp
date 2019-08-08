// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniYourPartsWidget.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "UI/UIAssets.h"
#include "UI/MiniCardWidget.h"
#include "Parts/RobotPart.h"

void UMiniYourPartsWidget::AddDisplayedPart(URobotPart* RobotPart)
{
  UE_LOG(LogUI, Verbose, TEXT("%s::AddDisplayedPart"), *GetName());
  UE_LOG(LogUI, VeryVerbose, TEXT("%s::AddDisplayedPart - %s"), *GetName(), *RobotPart->PartName.ToString());

// don't display cards that are currently assigned to the robot
// or default parts
  if (!RobotPart->IsAssignedTo(CurrentDraft->PartAssignment) && !RobotPart->IsDefaultPart())
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetWorld()->GetGameInstance());
    UMiniCardWidget* Card = CreateWidget<UMiniCardWidget>(GetOwningPlayer(), GameInstance->AssetsBP->UIAssetsBP->MiniCardWidgetBP); 
    Card->bCanBeDragged = true;
    Card->SetRobotPart(RobotPart);
    DisplayedCards->AddChild(Card);
    NewCardAddedDelegate.Broadcast(Card);
  }
}
