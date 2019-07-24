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

  SetupRobotPartPool();

  ASoloDraftPlayerController* PC = Cast<ASoloDraftPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

//  OnNextPackReady.AddDynamic(PC, &ASoloDraftPlayerController::OnNextPack);

//  PC->PartDraftedDelegate.AddDynamic(this, &ASoloDraftGameState::ServerDraftPart);

  if (CurrentDraft->CurrentPack.Num() == 0)
  {
    NextPack();
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
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5002));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5003));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5004));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(1005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(2005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(3005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(4005));
    RobotPartPool.Add(GameInstance->PartSingleton->PartDB.GetPart(5005));
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

