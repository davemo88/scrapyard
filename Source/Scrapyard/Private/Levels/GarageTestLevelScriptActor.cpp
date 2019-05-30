// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageTestLevelScriptActor.h"
#include "Game/ScrapyardGameInstance.h"
#include "Player/RobotPlayerController.h"
#include "Robots/RobotCharacter.h"


void AGarageTestLevelScriptActor::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay(); 

  UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>();
  if (GameInstance->PartAssignment != NULL)
  {
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();   
    ARobotCharacter* Char = Cast<ARobotCharacter>(PlayerController->GetPawn());
    if (Char != nullptr && GameInstance->PartAssignment->IsComplete())
    {
      Char->RobotBodyComponent->PartAssignment->SetAssignment(GameInstance->PartAssignment);
    }
  }

  SpawnTestDrones();
}

void AGarageTestLevelScriptActor::SpawnTestDrones()
{
  UWorld* World = GetWorld();
  
  TestDrone1 = World->SpawnActor<ADrone>(FVector(-1000.0f, 1000.0f, 200.0f), FRotator::ZeroRotator, FActorSpawnParameters());
  TestDrone2 = World->SpawnActor<ADrone>(FVector(-1000.0f, -1000.0f, 200.0f), FRotator::ZeroRotator, FActorSpawnParameters());
  TestDrone1->Team = 1;
  TestDrone2->Team = 1;
//  TestDrone3 = World->SpawnActor<ADrone>(FVector(-1000.0f, 1000.0f, 200.0f), FRotator::ZeroRotator, FActorSpawnParameters());
}
