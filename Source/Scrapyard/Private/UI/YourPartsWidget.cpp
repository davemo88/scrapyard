// Fill out your copyright notice in the Description page of Project Settings.


#include "YourPartsWidget.h"
#include "Scrapyard.h"
#include "UI/PartCardWidget.h"
#include "UI/PartCardDragDropOperation.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/SoloDraftGameState.h"
#include "Game/ScrapyardAssets.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/HandheldPart.h"


void UYourPartsWidget::NativeConstruct()
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();
//  CurrentDraft = GetWorld()->GetGameState<ASoloDraftGameState>()->CurrentDraft;

  AllFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnAllFilterButtonClicked);
  HeadFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnHeadFilterButtonClicked);
  CoreFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnCoreFilterButtonClicked);
  ArmsFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnArmsFilterButtonClicked);
  LegsFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnLegsFilterButtonClicked);
  HandheldFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnHandheldFilterButtonClicked);
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

void UYourPartsWidget::ClearDisplayedCards()
{
  DisplayedCards->ClearChildren();
}

void UYourPartsWidget::AddDisplayedCard(UPartCardWidget* Card)
{
  DisplayedCards->AddChild(Card);
}

void UYourPartsWidget::AddDisplayedPart(URobotPart* RobotPart)
{
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetWorld()->GetGameInstance());
  UPartCardWidget* Card = CreateWidget<UPartCardWidget>(GetOwningPlayer(), GameInstance->AssetsBP->UIAssetsBP->PartCardWidgetBP); 
  Card->SetRobotPart(RobotPart);
  AddDisplayedCard(Card);
  NewPartCardAdded.Broadcast(Card);
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
}

void UYourPartsWidget::OnAllFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnAllFilterButtonClicked"), *GetName());
  DisplayAll();
}

void UYourPartsWidget::OnHeadFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnHeadFilterButtonClicked"), *GetName());
  DisplayParts(CurrentDraft->DraftedParts.FilterByPredicate([](URobotPart* Part){return Cast<UHeadPart>(Part) != nullptr;}));
}

void UYourPartsWidget::OnCoreFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnCoreFilterButtonClicked"), *GetName());
  DisplayParts(CurrentDraft->DraftedParts.FilterByPredicate([](URobotPart* Part){return Cast<UCorePart>(Part) != nullptr;}));
}

void UYourPartsWidget::OnArmsFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnArmsFilterButtonClicked"), *GetName());
  DisplayParts(CurrentDraft->DraftedParts.FilterByPredicate([](URobotPart* Part){return Cast<UArmsPart>(Part) != nullptr;}));
}

void UYourPartsWidget::OnLegsFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnLegsFilterButtonClicked"), *GetName());
  DisplayParts(CurrentDraft->DraftedParts.FilterByPredicate([](URobotPart* Part){return Cast<ULegsPart>(Part) != nullptr;}));
}

void UYourPartsWidget::OnHandheldFilterButtonClicked()
{
  UE_LOG(LogUI, Log, TEXT("%s::OnHandheldFilterButtonClicked"), *GetName());
  DisplayParts(CurrentDraft->DraftedParts.FilterByPredicate([](URobotPart* Part){return Cast<UHandheldPart>(Part) != nullptr;}));
}

