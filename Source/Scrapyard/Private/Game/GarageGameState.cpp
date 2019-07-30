// Fill out your copyright notice in the Description page of Project Settings.


#include "GarageGameState.h"
#include "Game/ScrapyardGameInstance.h"
#include "Levels/GarageLevelScriptActor.h"
#include "Robots/RobotCharacter.h"

AGarageGameState::AGarageGameState()
{

}

void AGarageGameState::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();
  SetCurrentDraft();
}

void AGarageGameState::SetCurrentDraft()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetCurrentDraft"), *GetName());
  if (UScrapyardGameInstance* GameInstance = GetGameInstance<UScrapyardGameInstance>())
  {
    if (GameInstance->SoloDraft != nullptr)
    {
      UE_LOG(LogTemp, Log, TEXT("%s::SetCurrentDraft - loading draft from game instance"), *GetName());
      CurrentDraft = DuplicateObject<USoloDraft>(GameInstance->SoloDraft, nullptr);
    }
    else
    {
      UE_LOG(LogTemp, Log, TEXT("%s::SetCurrentDraft - creating fresh draft"), *GetName());
      CurrentDraft = NewObject<USoloDraft>();
    }
  }

  if (AGarageLevelScriptActor* GarageLSA = Cast<AGarageLevelScriptActor>(GetWorld()->GetLevelScriptActor()))
  {
    GarageLSA->GetRobotCharacter()->SetPartAssignment(CurrentDraft->PartAssignment);
  }
}

void AGarageGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  UE_LOG(LogGameState, Log, TEXT("%s::EndPlay"), *GetName());
  if (UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>())
  {
    GameInstance->SoloDraft = DuplicateObject<USoloDraft>(CurrentDraft, nullptr);
  }
  Super::EndPlay(EndPlayReason);
}

