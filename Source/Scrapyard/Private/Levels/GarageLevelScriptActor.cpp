// Fill out your copyright notice in the Description page of Project Settings.


#include "GarageLevelScriptActor.h"
#include "Game/ScrapyardGameInstance.h"
#include "Robots/RobotCharacter.h"
#include "Parts/RobotPart.h"
#include "Engine/World.h"
#include "Parts/RobotPartAssignment.h"
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
  UE_LOG(LogTemp, Warning, TEXT("%s::SpawnRobotCharacter"), *GetName());
  UWorld* World = GetWorld();
  RobotCharacter = World->SpawnActor<ARobotCharacter>(FVector(0.0f, 0.0f, 70.0f), FRotator(0.0f, 90.0f, 0.0f), FActorSpawnParameters());
  RobotCharacter->RobotBodyComponent->SetEnableGravity(false);
  UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>();
  if (GameInstance->PartAssignment != nullptr)
  {
    RobotCharacter->RobotBodyComponent->PartAssignment->SetAssignment(GameInstance->PartAssignment); 
  }
}

ARobotCharacter* AGarageLevelScriptActor::GetRobotCharacter() const
{
  return RobotCharacter;
}
