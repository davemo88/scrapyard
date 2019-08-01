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

  SetCurrentDraft();

  SetupRobotPartPool();

  if (CurrentDraft->CurrentPack.Num() == 0)
  {
    NextPack();
  }

}

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

void ASoloDraftGameState::SetupRobotPartPool()
{
  if (UScrapyardGameInstance* GameInstance = UScrapyardGameInstance::GameInstance)
  {
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1001));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2001));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3001));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4001));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5001));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(6001));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(6002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(6003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(6004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(6005));
  }
}

void ASoloDraftGameState::NextPack()
{
  SamplePack();
  OnNextPackReady.Broadcast();
}

void ASoloDraftGameState::SamplePack()
{
  CurrentDraft->CurrentPack.Empty();

  URobotPart* PotentialPart;
  while (CurrentDraft->CurrentPack.Num() < CurrentDraft->ChoicesPerPick)
  {
    PotentialPart = SamplePart();
    if (!CurrentDraft->CurrentPack.Contains(PotentialPart))
    {
      CurrentDraft->CurrentPack.Add(PotentialPart);
    }
  }
}

URobotPart* ASoloDraftGameState::SamplePart()
{
  return RobotPartPool[FMath::RandRange(0, RobotPartPool.Num() - 1)];
}

bool ASoloDraftGameState::ServerDraftPart_Validate(URobotPart* RobotPart)
{
  UE_LOG(LogDraft, Log, TEXT("%s::ServerDraftPart_Validate"), *GetName());
  return true;
}

void ASoloDraftGameState::ServerDraftPart_Implementation(URobotPart* RobotPart)
{
  UE_LOG(LogDraft, Log, TEXT("%s::ServerDraftPart_Implementation"), *GetName());
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

