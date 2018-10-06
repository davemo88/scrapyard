// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftPlayerController.h"
#include "SoloDraftWidget.h"

void ASoloDraftPlayerController::SetupWidget()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetupWidget"), *GetName());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  Widget = CreateWidget<USoloDraftWidget>(this, GameInstance->DefaultAssetsBP->SoloDraftWidgetBP);
//  Widget = CreateWidget<UGarageWidget>(this, GameInstance->DefaultAssetsBP->GarageWidgetBP);
  Widget->AddToViewport();
}

void ASoloDraftPlayerController::OnNextPack()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnNextPack"), *GetName());
  if (Widget)
  {
    UE_LOG(LogTemp, Warning, TEXT("Widget is live"), *GetName());
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Widget is not live"), *GetName());
  }
  
}

void ASoloDraftPlayerController::RemoveCardWidgets()
{

}

void ASoloDraftPlayerController::AddCardWidgets()
{

}

void ASoloDraftPlayerController::OnPartDrafted()
{

}

