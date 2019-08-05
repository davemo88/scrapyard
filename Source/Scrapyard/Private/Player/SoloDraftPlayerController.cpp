// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftPlayerController.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Game/SoloDraftGameState.h"
#include "UI/SoloDraftWidget.h"
#include "Parts/RobotPart.h"

ASoloDraftPlayerController::ASoloDraftPlayerController()
{
  UE_LOG(LogController, Log, TEXT("ASoloDraftPlayerController::ASoloDraftPlayerController"));
}

void ASoloDraftPlayerController::SetupWidget()
{
  UE_LOG(LogController, Log, TEXT("%s::SetupWidget"), *GetName());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  SoloDraftWidget = CreateWidget<USoloDraftWidget>(this, GameInstance->AssetsBP->UIAssetsBP->SoloDraftWidgetBP);
  SoloDraftWidget->SetCurrentDraft(GetWorld()->GetGameState<ASoloDraftGameState>()->CurrentDraft);
  SoloDraftWidget->PartDraftedDelegate.AddDynamic(this, &ASoloDraftPlayerController::OnPartDrafted);
  
  if (ASoloDraftGameState* SoloDraftGS = GetWorld()->GetGameState<ASoloDraftGameState>())
  {
    SoloDraftGS->OnNextPackReady.AddDynamic(SoloDraftWidget, &USoloDraftWidget::NextPack);
  }

  SoloDraftWidget->AddToViewport();
  SoloDraftWidget->NextPack();
}

void ASoloDraftPlayerController::OnPartDrafted(URobotPart* DraftedPart)
{
  UE_LOG(LogController, Log, TEXT("%s::OnPartDrafted"), *GetName());  

  if (ASoloDraftGameState* SoloDraftGS = GetWorld()->GetGameState<ASoloDraftGameState>())
  {
    SoloDraftGS->ServerDraftPart(DraftedPart);
  }

}
