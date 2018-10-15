// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftPlayerController.h"
#include "SoloDraftWidget.h"
#include "Parts/RobotPart.h"
#include "UI/PartCardWidget.h"
#include "UI/YourPartsWidget.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

ASoloDraftPlayerController::ASoloDraftPlayerController()
{
  UE_LOG(LogTemp, Warning, TEXT("ASoloDraftPlayerController::ASoloDraftPlayerController"));
}

void ASoloDraftPlayerController::SetupWidget()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetupWidget"), *GetName());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  SoloDraftWidget = CreateWidget<USoloDraftWidget>(this, GameInstance->DefaultAssetsBP->SoloDraftWidgetBP);
  SoloDraftWidget->AddToViewport();
}

void ASoloDraftPlayerController::OnNextPack()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnNextPack"), *GetName());
  if (SoloDraftWidget)
  {
    ASoloDraftGameState* GameState = GetWorld()->GetGameState<ASoloDraftGameState>();
    TArray<URobotPart*> NextPack = GameState->CurrentDraft->CurrentPack;
    UE_LOG(LogTemp, Warning, TEXT("Widget is live"), *GetName());
    UE_LOG(LogTemp, Warning, TEXT("Next Pack has %i items"), NextPack.Num());
    SoloDraftWidget->PackDisplayPanel->ClearChildren();
    for (int32 i = 0; i < NextPack.Num(); ++i)
    {
      UE_LOG(LogTemp, Warning, TEXT("creating card for %s"), *NextPack[i]->PartName);
      UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
      UPartCardWidget* Card = CreateWidget<UPartCardWidget>(this, GameInstance->DefaultAssetsBP->PartCardWidgetBP); 
      Card->SetRobotPart(NextPack[i]);
      Card->CardMouseEnteredDelegate.AddDynamic(this, & ASoloDraftPlayerController::OnPartCardHovered);
      Card->CardDoubleClickedDelegate.AddDynamic(this, &ASoloDraftPlayerController::OnPartDoubleClicked);
      SoloDraftWidget->PackDisplayPanel->AddChild(Card);
      if (UUniformGridSlot* Slot = Cast<UUniformGridSlot>(Card->Slot))
      {
        Slot->SetColumn(i);
      }

    }
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Widget is not live"), *GetName());
  }
  
}

void ASoloDraftPlayerController::OnPartDoubleClicked(URobotPart* RobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnPartDrafted"), *GetName());  

  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  UPartCardWidget* PartCard = CreateWidget<UPartCardWidget>(this, GameInstance->DefaultAssetsBP->PartCardWidgetBP); 

  PartCard->SetRobotPart(RobotPart);
  SoloDraftWidget->YourPartsWidget->AddDisplayedCard(PartCard);

  PartDraftedDelegate.Broadcast(RobotPart);

  SoloDraftWidget->UpdatePickCounter();
}

void ASoloDraftPlayerController::OnPartCardHovered(URobotPart* RobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnPartCardHovered"), *GetName());  
}
