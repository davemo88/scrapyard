// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageTestLevelScriptActor.h"
#include "Game/ScrapyardGameInstance.h"
#include "RobotPlayerController.h"
#include "Robots/RobotCharacter.h"


void AGarageTestLevelScriptActor::BeginPlay()
{
  Super::BeginPlay(); 

  UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>();
  if (GameInstance->PartAssignment != NULL)
  {
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();   
    ARobotCharacter* Char = Cast<ARobotCharacter>(PlayerController->GetPawn());
    if (Char != NULL)
    {
      UE_LOG(LogTemp, Warning, TEXT("Got the char!"));
      UE_LOG(LogTemp, Warning, TEXT("Got the char!"));

    }
  }
}

