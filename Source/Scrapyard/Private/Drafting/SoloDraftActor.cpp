// Fill out your copyright notice in the Description page of Project Settings.

#include "SoloDraftActor.h"
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
#include "Game/SoloDraftGameState.h"

// maybe make this a gamestate?

// Sets default values
ASoloDraftActor::ASoloDraftActor()
{
  UE_LOG(LogTemp, Warning, TEXT("ASoloDraftActor::ASoloDraftActor"));
// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//  PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoloDraftActor::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();

  SetupRobotPartPool();

  ASoloDraftPlayerController* PC = Cast<ASoloDraftPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

  OnNextPackReady.AddDynamic(PC, &ASoloDraftPlayerController::OnNextPack);

  PC->OnWidgetReadyDelegate.AddDynamic(this, &ASoloDraftActor::OnSoloDraftWidgetReady);
  PC->PartDraftedDelegate.AddDynamic(this, &ASoloDraftActor::ServerDraftPart);

}

void ASoloDraftActor::OnSoloDraftWidgetReady()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnSoloDraftWidgetReady"), *GetName());
  NextPack();
}

// Called every frame
void ASoloDraftActor::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

void ASoloDraftActor::SetupRobotPartPool()
{
  RobotPartPool.Add(URobotPart::PartDB.GetPart<URobotPart>(1000));
  RobotPartPool.Add(URobotPart::PartDB.GetPart<URobotPart>(2000));
  RobotPartPool.Add(URobotPart::PartDB.GetPart<URobotPart>(3000));
  RobotPartPool.Add(URobotPart::PartDB.GetPart<URobotPart>(4000));
}

void ASoloDraftActor::NextPack()
{
  SamplePack();
  OnNextPackReady.Broadcast();
}

void ASoloDraftActor::SamplePack()
{
//  if (Role == ROLE_Authority)
//  {
  ASoloDraftGameState* GameState = GetWorld()->GetGameState<ASoloDraftGameState>();
  USoloDraft* CurrentDraft = GameState->CurrentDraft;

  CurrentDraft->CurrentPack.Empty();

  for (uint32 i = 0; i < NumChoices; ++i)
  {
    CurrentDraft->CurrentPack.Add(SamplePart());
  }

  OnNextPackReady.Broadcast();
}

URobotPart* ASoloDraftActor::SamplePart(bool Replacement)
{
  URobotPart* RobotPart = nullptr;
  int Index = FMath::RandRange(0, RobotPartPool.Num() - 1);
  RobotPart = RobotPartPool[Index];
  if (!Replacement)
  {
    RobotPartPool.RemoveAt(Index);
  }
  return RobotPart;
}

bool ASoloDraftActor::ServerDraftPart_Validate(URobotPart* RobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ServerDraftPart_Validate"), *GetName());
  return true;
}

void ASoloDraftActor::ServerDraftPart_Implementation(URobotPart* RobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ServerDraftPart_Implementation"), *GetName());
  ASoloDraftGameState* GameState = GetWorld()->GetGameState<ASoloDraftGameState>();
  USoloDraft* CurrentDraft = GameState->CurrentDraft;
  UE_LOG(LogTemp, Warning, TEXT("drafting a part"));
  CurrentDraft->NumPicks++;
  RobotPart->Draft(CurrentDraft);

  UE_LOG(LogTemp, Warning, TEXT("num heads %i"), CurrentDraft->DraftedHeads.Num());
  UE_LOG(LogTemp, Warning, TEXT("num cores %i"), CurrentDraft->DraftedCores.Num());
  UE_LOG(LogTemp, Warning, TEXT("num arms %i"), CurrentDraft->DraftedArms.Num());
  UE_LOG(LogTemp, Warning, TEXT("num legs %i"), CurrentDraft->DraftedLegs.Num());

  if (CurrentDraft->NumPicks < CurrentDraft->MaxPicks)
  {
    NextPack();
  }
  else
// this should be an event
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
    if (CurrentDraft != nullptr)
    {
      UE_LOG(LogTemp, Warning, TEXT("draft complete"));
      GameInstance->SoloDraft = DuplicateObject(CurrentDraft, NULL);
      UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/GarageLevel");
    }
  }
}
