// Fill out your copyright notice in the Description page of Project Settings.


#include "GarageLevelScriptActor.h"
#include "Game/ScrapyardGameInstance.h"
#include "Robots/RobotCharacter.h"
#include "Parts/RobotPart.h"
#include "Engine/World.h"
#include "Parts/PartAssignment.h"
#include "Robots/RobotBodyComponent.h"


void AGarageLevelScriptActor::BeginPlay()
{
  Super::BeginPlay();

  SoloDraft = GetCurrentSoloDraft();

  SpawnRobotCharacter();
}

USoloDraft* AGarageLevelScriptActor::GetCurrentSoloDraft() const
{
  UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>();
  return GameInstance->SoloDraft;
}

void AGarageLevelScriptActor::SpawnRobotCharacter()
{
  UWorld* World = GetWorld();
  RobotCharacter = World->SpawnActor<ARobotCharacter>(FVector(300.0f, 0.0f, 200.0f), FRotator(-10.0f, 180.0f, 0.f), FActorSpawnParameters());
  RobotCharacter->RobotBodyComponent->SetEnableGravity(false);
  UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>();
  if (GameInstance->PartAssignment != nullptr)
  {
    RobotCharacter->PartAssignment->SetAssignment(GameInstance->PartAssignment); 
  }
}

ARobotCharacter* AGarageLevelScriptActor::GetRobotCharacter() const
{
  return RobotCharacter;
}
