// Fill out your copyright notice in the Description page of Project Settings.


#include "GarageLevelScriptActor.h"
#include "Game/GarageGameState.h"
#include "Robots/RobotCharacter.h"
#include "Engine/World.h"
#include "Parts/PartAssignment.h"
#include "Drafting/SoloDraft.h"


void AGarageLevelScriptActor::BeginPlay()
{
  Super::BeginPlay();

  SpawnRobotCharacter();
}

void AGarageLevelScriptActor::SpawnRobotCharacter()
{
  UWorld* World = GetWorld();
  RobotCharacter = World->SpawnActor<ARobotCharacter>(FVector(300.0f, 180.0f, 150.0f), FRotator(-10.0f, 200.0f, 0.f), FActorSpawnParameters());
  RobotCharacter->RobotBodyComponent->SetEnableGravity(false);
  
  if (AGarageGameState* GarageGS = World->GetGameState<AGarageGameState>())
  {
    RobotCharacter->PartAssignment->SetAssignment(GarageGS->CurrentDraft->PartAssignment); 
  }
}

ARobotCharacter* AGarageLevelScriptActor::GetRobotCharacter()
{
  return RobotCharacter;
}
