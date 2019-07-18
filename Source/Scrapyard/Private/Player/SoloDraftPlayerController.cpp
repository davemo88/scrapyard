// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftPlayerController.h"
#include "SoloDraftWidget.h"
#include "Parts/RobotPart.h"
#include "UI/PartCardWidget.h"
#include "UI/YourPartsWidget.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Game/SoloDraftGameState.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

ASoloDraftPlayerController::ASoloDraftPlayerController()
{
  UE_LOG(LogController, Log, TEXT("ASoloDraftPlayerController::ASoloDraftPlayerController"));
}

void ASoloDraftPlayerController::SetupWidget()
{
  UE_LOG(LogController, Log, TEXT("%s::SetupWidget"), *GetName());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  SoloDraftWidget = CreateWidget<USoloDraftWidget>(this, GameInstance->AssetsBP->UIAssetsBP->SoloDraftWidgetBP);
  SoloDraftWidget->YourPartsWidget->CurrentDraft = GetWorld()->GetGameState<ASoloDraftGameState>()->CurrentDraft;
  SoloDraftWidget->AddToViewport();
}

void ASoloDraftPlayerController::OnNextPack()
{
  UE_LOG(LogController, Log, TEXT("%s::OnNextPack"), *GetName());
  SoloDraftWidget->NextPack();
}

void ASoloDraftPlayerController::OnPartDrafted(URobotPart* RobotPart)
{
  UE_LOG(LogController, Log, TEXT("%s::OnPartDrafted"), *GetName());  

  PartDraftedDelegate.Broadcast(RobotPart);

  SoloDraftWidget->YourPartsWidget->AddDisplayedPart(RobotPart);

  SoloDraftWidget->UpdatePickCounter();
}

void ASoloDraftPlayerController::OnPartCardHovered(URobotPart* RobotPart)
{
  UE_LOG(LogController, Log, TEXT("%s::OnPartCardHovered"), *GetName());  
}
