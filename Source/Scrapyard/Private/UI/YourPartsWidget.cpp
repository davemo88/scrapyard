// Fill out your copyright notice in the Description page of Project Settings.


#include "YourPartsWidget.h"
#include "UI/PartCardWidget.h"
#include "SoloDraft.h"
#include "Game/SoloDraftGameState.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"

void UYourPartsWidget::NativeConstruct()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeConstruct"), *GetName());
  CurrentDraft = GetWorld()->GetGameState<ASoloDraftGameState>()->CurrentDraft;

  AllFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnAllFilterButtonClicked);
  HeadFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnHeadFilterButtonClicked);
  CoreFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnCoreFilterButtonClicked);
  ArmsFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnArmsFilterButtonClicked);
  LegsFilterButton->OnClicked.AddDynamic(this, &UYourPartsWidget::OnLegsFilterButtonClicked);
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
  UPartCardWidget* Card = CreateWidget<UPartCardWidget>(GetOwningPlayer(), GameInstance->DefaultAssetsBP->PartCardWidgetBP); 
  Card->SetRobotPart(RobotPart);
  AddDisplayedCard(Card);
}

void UYourPartsWidget::DisplayParts(TArray<URobotPart*> Parts)
{
  ClearDisplayedCards(); 
  for (int32 i=0; i<Parts.Num(); ++i)
  {
    AddDisplayedPart(Parts[i]);
  }
}

void UYourPartsWidget::OnAllFilterButtonClicked()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnAllFilterButtonClicked"), *GetName());
  TArray<URobotPart*> AllParts; 
  AllParts.Append(CurrentDraft->DraftedHeads);
  AllParts.Append(CurrentDraft->DraftedCores);
  AllParts.Append(CurrentDraft->DraftedArms);
  AllParts.Append(CurrentDraft->DraftedLegs);
  DisplayParts(AllParts);
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

