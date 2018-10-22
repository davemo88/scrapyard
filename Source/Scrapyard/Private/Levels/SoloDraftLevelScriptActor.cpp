// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftLevelScriptActor.h"
#include "SoloDraftActor.h"

void ASoloDraftLevelScriptActor::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();

  UWorld* World = GetWorld();
  World->SpawnActor<ASoloDraftActor>(FVector::ZeroVector, FRotator::ZeroRotator, FActorSpawnParameters());
}

