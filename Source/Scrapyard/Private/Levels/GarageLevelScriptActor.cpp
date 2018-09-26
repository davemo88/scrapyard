// Fill out your copyright notice in the Description page of Project Settings.


#include "GarageLevelScriptActor.h"
#include "Game/ScrapyardGameInstance.h"


void AGarageLevelScriptActor::BeginPlay()
{
  Super::BeginPlay();

  SoloDraft = GetCurrentSoloDraft();

  SpawnRobotPartCardActor();
}

USoloDraft* AGarageLevelScriptActor::GetCurrentSoloDraft()
{
  UScrapyardGameInstance* GameInstance = GetWorld()->GetGetInstance();
}

void AGarageLevelScriptActor::SpawnRobotBodyGarage()
{

}

void AssignPart(URobotPart* Part)
{
  Part->Assign(RobotBodyGarage);
}
