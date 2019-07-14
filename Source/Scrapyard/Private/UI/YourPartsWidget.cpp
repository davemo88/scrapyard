// Fill out your copyright notice in the Description page of Project Settings.


#include "YourPartsWidget.h"
#include "UI/PartCardWidget.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/SoloDraftGameState.h"
#include "Game/ScrapyardAssets.h"

void UYourPartsWidget::NativeConstruct()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();
//  CurrentDraft = GetWorld()->GetGameState<ASoloDraftGameState>()->CurrentDraft;

  AllFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnAllFilterButtonClicked);
  HeadFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnHeadFilterButtonClicked);
  CoreFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnCoreFilterButtonClicked);
  ArmsFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnArmsFilterButtonClicked);
  LegsFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnLegsFilterButtonClicked);
  HandheldFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnHandheldFilterButtonClicked);
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
  TArray<URobotPart*> AllParts; 
  AllParts.Append(CurrentDraft->DraftedHeads);
  AllParts.Append(CurrentDraft->DraftedCores);
  AllParts.Append(CurrentDraft->DraftedArms);
  AllParts.Append(CurrentDraft->DraftedLegs);
  AllParts.Append(CurrentDraft->DraftedHandhelds);
  DisplayParts(AllParts);
}

void UYourPartsWidget::OnAllFilterButtonClicked()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnAllFilterButtonClicked"), *GetName());
  DisplayAll();
}

void UYourPartsWidget::OnHeadFilterButtonClicked()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnHeadFilterButtonClicked"), *GetName());
  DisplayParts(CurrentDraft->DraftedHeads);
}

void UYourPartsWidget::OnCoreFilterButtonClicked()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnCoreFilterButtonClicked"), *GetName());
  DisplayParts(CurrentDraft->DraftedCores);
}

void UYourPartsWidget::OnArmsFilterButtonClicked()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnArmsFilterButtonClicked"), *GetName());
  DisplayParts(CurrentDraft->DraftedArms);
}

void UYourPartsWidget::OnLegsFilterButtonClicked()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnLegsFilterButtonClicked"), *GetName());
  DisplayParts(CurrentDraft->DraftedLegs);
}

void UYourPartsWidget::OnHandheldFilterButtonClicked()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnHandheldFilterButtonClicked"), *GetName());
  DisplayParts(CurrentDraft->DraftedHandhelds);
}

