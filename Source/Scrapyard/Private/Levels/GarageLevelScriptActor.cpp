// Fill out your copyright notice in the Description page of Project Settings.


#include "GarageLevelScriptActor.h"
#include "Game/ScrapyardGameInstance.h"
#include "Robots/RobotBodyGarage.h"
#include "Parts/RobotPart.h"


void AGarageLevelScriptActor::BeginPlay()
{
  Super::BeginPlay();

  SoloDraft = GetCurrentSoloDraft();

  SpawnRobotBodyGarage();
}

USoloDraft* AGarageLevelScriptActor::GetCurrentSoloDraft()
{
  UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>();
  return GameInstance->SoloDraft;
}

void AGarageLevelScriptActor::SpawnRobotBodyGarage()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SpawnRobotBodyGarage"), *GetName());
  UWorld* World = GetWorld();
  RobotBodyGarage = World->SpawnActor<ARobotBodyGarage>(FVector(0.0f, 0.0f, 70.0f), FRotator(0.0f, 90.0f, 0.0f), FActorSpawnParameters());
}

ARobotBodyGarage* AGarageLevelScriptActor::GetRobotBodyGarage()
{
  return RobotBodyGarage;
}
