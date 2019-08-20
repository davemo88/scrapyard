// Fill out your copyright notice in the Description page of Project Settings.


#include "GarageLevelScriptActor.h"
#include "Game/GarageGameState.h"
#include "Robots/RobotCharacter.h"
#include "Engine/World.h"
#include "Parts/PartAssignment.h"
#include "Drafting/SoloDraft.h"


void AGarageLevelScriptActor::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();

  SpawnRobotCharacter();
}

void AGarageLevelScriptActor::SpawnRobotCharacter()
{
  UWorld* World = GetWorld();
  RobotCharacter = World->SpawnActor<ARobotCharacter>(FVector(175.0f, 190.0f, 100.0f), FRotator(-10.0f, 200.0f, 0.f), FActorSpawnParameters());
  RobotCharacter->RobotBodyComponent->SetEnableGravity(false);
}

ARobotCharacter* AGarageLevelScriptActor::GetRobotCharacter()
{
  return RobotCharacter;
}
