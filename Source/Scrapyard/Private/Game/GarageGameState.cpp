// Fill out your copyright notice in the Description page of Project Settings.


#include "GarageGameState.h"
#include "Game/ScrapyardGameInstance.h"

AGarageGameState::AGarageGameState()
{
  SetCurrentDraft();
}

void AGarageGameState::SetCurrentDraft()
{
  if (GetWorld())
  {
    UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>();
    if (GameInstance != nullptr && GameInstance->SoloDraft != nullptr)
    {
      CurrentDraft = DuplicateObject<USoloDraft>(GameInstance->SoloDraft, nullptr);
    }
    else
    {
      CurrentDraft = NewObject<USoloDraft>();
    }
  }
}


