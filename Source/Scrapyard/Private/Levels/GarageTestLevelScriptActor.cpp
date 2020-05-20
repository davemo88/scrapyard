// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageTestLevelScriptActor.h"
#include "Game/ScrapyardGameInstance.h"
#include "Player/RobotPlayerController.h"
#include "Robots/RobotCharacter.h"
#include "Drafting/SoloDraft.h"
#include "Kismet/GameplayStatics.h"

AGarageTestLevelScriptActor::AGarageTestLevelScriptActor()
{
  NumDrones = 1;
}


void AGarageTestLevelScriptActor::BeginPlay()
{
  Super::BeginPlay(); 

  UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>();
  if (GameInstance->CurrentDraft != NULL)
  {
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();   
    ARobotCharacter* Char = Cast<ARobotCharacter>(PlayerController->GetPawn());
    if (Char != nullptr && GameInstance->CurrentDraft->PartAssignment->IsComplete())
    {
      Char->SetPartAssignment(GameInstance->CurrentDraft->PartAssignment);
    }
  }

  SpawnTestDrones();
}

void AGarageTestLevelScriptActor::SpawnTestDrones()
{
  UWorld* World = GetWorld();
  
  auto SpawnTransform1 = FTransform(FVector(-1000.0f, 1000.0f, 200.0f));
  auto SpawnTransform2 = FTransform(FVector(-1000.0f, -1000.0f, 200.0f));
  TestDrone1 = Cast<ADrone>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ADrone::StaticClass(), SpawnTransform1));
  TestDrone2 = Cast<ADrone>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ADrone::StaticClass(), SpawnTransform2));
  TestDrone1->Team = 1;
  TestDrone2->Team = 1;
  UGameplayStatics::FinishSpawningActor(TestDrone1, SpawnTransform1);
  UGameplayStatics::FinishSpawningActor(TestDrone2, SpawnTransform2);

  ADrone* NextDrone;
  auto SpawnTransform = FTransform(FVector(5000.0f, 0.0f, 200.0f));
  for (int32 i = 0; i < NumDrones; ++i)
  {
    SpawnTransform.AddToTranslation(FVector(0.0f, 1000.0f, 0.0f));
    NextDrone = Cast<ADrone>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ADrone::StaticClass(), SpawnTransform1)); 
    NextDrone->Team = 1;
    UGameplayStatics::FinishSpawningActor(NextDrone, SpawnTransform);
  }

}

void AGarageTestLevelScriptActor::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);
}
