// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftLevelScriptActor.h"
#include "Drafting/SoloDraftActor.h"

void ASoloDraftLevelScriptActor::BeginPlay()
{
  Super::BeginPlay();

  UWorld* World = GetWorld();
// TODO: seems like this functionality should be shared between gamestate and level script actor
  World->SpawnActor<ASoloDraftActor>(FVector::ZeroVector, FRotator::ZeroRotator, FActorSpawnParameters());
}

