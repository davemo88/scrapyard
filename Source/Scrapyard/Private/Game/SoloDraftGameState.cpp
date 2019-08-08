// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftGameState.h"
#include "Scrapyard.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "UObjectGlobals.h"
#include "Game/ScrapyardGameInstance.h"
#include "Drafting/SoloDraft.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Player/SoloDraftPlayerController.h"

ASoloDraftGameState::ASoloDraftGameState()
{

}

void ASoloDraftGameState::BeginPlay()
{
  UE_LOG(LogDraft, Log, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();

<<<<<<< HEAD
  SetCurrentDraft();

=======
>>>>>>> caecc36df94501247f28bddf555caf2098a5035a
  if (CurrentDraft->CurrentPick == 0)
  {
    NextPack();
  }

}

<<<<<<< HEAD
void ASoloDraftGameState::SetCurrentDraft()
{
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());

  if (GameInstance->CurrentDraft != nullptr)
  {
    UE_LOG(LogDraft, Log, TEXT("%s::SetCurrentDraft - loading draft from game state"), *GetName());
    CurrentDraft = DuplicateObject<USoloDraft>(GameInstance->CurrentDraft, nullptr);
  }
  else
  {
    UE_LOG(LogDraft, Log, TEXT("%s::SetCurrentDraft - creating fresh draft"), *GetName());
    CurrentDraft = NewObject<USoloDraft>();
  }
}

=======
>>>>>>> caecc36df94501247f28bddf555caf2098a5035a
void ASoloDraftGameState::NextPack()
{
  CurrentDraft->SamplePack();
  OnNextPackReady.Broadcast();
}

bool ASoloDraftGameState::ServerDraftPart_Validate(URobotPart* RobotPart)
{
  UE_LOG(LogDraft, Log, TEXT("%s::ServerDraftPart_Validate"), *GetName());
  return true;
}

void ASoloDraftGameState::ServerDraftPart_Implementation(URobotPart* RobotPart)
{
  UE_LOG(LogDraft, Log, TEXT("%s::ServerDraftPart_Implementation"), *GetName());
  RobotPart->Draft(CurrentDraft);
  RobotPartPool.Remove(RobotPart);
  CurrentDraft->CurrentPick++;

  if (CurrentDraft->CurrentPick < CurrentDraft->TotalPicks)
  {
    NextPack();
  }
  else
// this should be an event
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
    if (CurrentDraft != nullptr)
    {
      UE_LOG(LogDraft, Verbose, TEXT("draft complete"));
//      GameInstance->CurrentDraft = DuplicateObject(CurrentDraft, NULL);
      UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/GarageLevel");
    }
  }
}

void ASoloDraftGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  UE_LOG(LogDraft, Log, TEXT("%s::EndPlay"), *GetName());
  if (UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>())
  {
    GameInstance->CurrentDraft = DuplicateObject<USoloDraft>(CurrentDraft, nullptr);
  }
  Super::EndPlay(EndPlayReason);
}

