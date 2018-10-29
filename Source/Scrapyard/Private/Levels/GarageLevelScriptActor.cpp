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

void AGarageLevelScriptActor::GotoTestLevel()
{
// better to do proper level transition and move the entire robot body garage actor over ?
// either that or we want our part assignment abstraction back so we can just take the part classes instead of this whole component
  UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>();
  GameInstance->RobotBodyComponent = DuplicateObject<URobotBodyComponent>(RobotBodyGarage->RobotBodyComponent, nullptr);// GetOwningPlayer()->GetWorld());
  UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/GarageTestLevel");
}
