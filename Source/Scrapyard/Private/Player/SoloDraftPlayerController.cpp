// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftPlayerController.h"
#include "SoloDraftWidget.h"
#include "PartCardWidget.h"
#include "YourPartsWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"

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

void ASoloDraftPlayerController::OnNextPack(TArray<URobotPart*> NextPack)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnNextPack"), *GetName());
  if (SoloDraftWidget)
  {
    UE_LOG(LogTemp, Warning, TEXT("Widget is live"), *GetName());
    UE_LOG(LogTemp, Warning, TEXT("Next Pack has %i items"), NextPack.Num());
    AddCardWidgets(NextPack);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Widget is not live"), *GetName());
  }
  
}

void ASoloDraftPlayerController::RemoveCardWidgets()
{

}

void ASoloDraftPlayerController::AddCardWidgets(TArray<URobotPart*> Parts)
{
  for (int32 i = 0; i < Parts.Num(); ++i)
  {
    UE_LOG(LogTemp, Warning, TEXT("creating card for %s"), *Parts[i]->PartName);
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
    UPartCardWidget* PartCard = CreateWidget<UPartCardWidget>(this, GameInstance->DefaultAssetsBP->PartCardWidgetBP); 
    PartCard->SetRobotPart(Parts[i]);
    SoloDraftWidget->PackDisplayPanel->AddChildToUniformGrid(PartCard);
    if (UUniformGridSlot* Slot = Cast<UUniformGridSlot>(PartCard->Slot))
    {
     Slot->SetColumn(i%Parts.Num());
    }
    PartCard->MouseEnteredDelegate.AddDynamic(this, & ASoloDraftPlayerController::OnPartCardHovered);
    PartCard->PartCardClickedDelegate.AddDynamic(this, &ASoloDraftPlayerController::OnPartDrafted);
  }
}

void ASoloDraftPlayerController::OnPartDrafted(URobotPart* RobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnPartDrafted"), *GetName());  

  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  UPartCardWidget* PartCard = CreateWidget<UPartCardWidget>(this, GameInstance->DefaultAssetsBP->PartCardWidgetBP); 

  PartCard->SetRobotPart(RobotPart);
  SoloDraftWidget->YourPartsWidget->DisplayedPartsBox->AddChild(PartCard);
}

void ASoloDraftPlayerController::OnPartCardHovered(URobotPart* RobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnPartCardHovered"), *GetName());  
}
