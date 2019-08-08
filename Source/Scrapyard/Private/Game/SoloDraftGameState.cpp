// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftGameState.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "UObjectGlobals.h"
#include "ScrapyardGameInstance.h"
#include "SoloDraft.h"
#include "HeadPart.h"
#include "CorePart.h"
#include "ArmsPart.h"
#include "LegsPart.h"
#include "Player/SoloDraftPlayerController.h"

ASoloDraftGameState::ASoloDraftGameState()
{
  CurrentDraft = CreateDefaultSubobject<USoloDraft>(TEXT("CurrentDraft"));
}

void ASoloDraftGameState::BeginPlay()
{
  UE_LOG(LogGameState, Log, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();

  if (CurrentDraft->CurrentPick == 0)
  {
    NextPack();
  }

}

void ASoloDraftGameState::NextPack()
{
  CurrentDraft->SamplePack();
  OnNextPackReady.Broadcast();
}

bool ASoloDraftGameState::ServerDraftPart_Validate(URobotPart* RobotPart)
{
  UE_LOG(LogGameState, Log, TEXT("%s::ServerDraftPart_Validate"), *GetName());
  return true;
}

void ASoloDraftGameState::ServerDraftPart_Implementation(URobotPart* RobotPart)
{
  UE_LOG(LogGameState, Log, TEXT("%s::ServerDraftPart_Implementation"), *GetName());
  CurrentDraft->DraftPart(RobotPart);
  RobotPartPool.Remove(RobotPart);

  if (CurrentDraft->DraftedParts.Num() < CurrentDraft->TotalPicks)
  {
    NextPack();
  }
  else
// this should be an event
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
    if (CurrentDraft != nullptr)
    {
      UE_LOG(LogGameState, Verbose, TEXT("draft complete"));
      GameInstance->SoloDraft = DuplicateObject(CurrentDraft, NULL);
      UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/GarageLevel");
    }
  }
}

