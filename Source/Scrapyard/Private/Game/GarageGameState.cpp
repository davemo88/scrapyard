// Fill out your copyright notice in the Description page of Project Settings.


#include "GarageGameState.h"
#include "Game/ScrapyardGameInstance.h"
#include "Levels/GarageLevelScriptActor.h"
#include "Robots/RobotBodyComponent.h"

AGarageGameState::AGarageGameState()
{

}

void AGarageGameState::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  Super::BeginPlay();
  UWorld* World = GetWorld();
  RobotCharacter = World->SpawnActor<ARobotCharacter>(FVector(175.0f, 180.0f, 70.0f), FRotator(-10.0f, 200.0f, 0.f), FActorSpawnParameters());
  RobotCharacter->RobotBodyComponent->SetEnableGravity(false);
  SetCurrentDraft();
}

void AGarageGameState::SetCurrentDraft()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetCurrentDraft"), *GetName());
  if (UScrapyardGameInstance* GameInstance = GetGameInstance<UScrapyardGameInstance>())
  {
    if (GameInstance->CurrentDraft != nullptr)
    {
      UE_LOG(LogTemp, Log, TEXT("%s::SetCurrentDraft - loading draft from game instance"), *GetName());
      CurrentDraft = DuplicateObject<USoloDraft>(GameInstance->CurrentDraft, nullptr);
    }
    else
    {
      UE_LOG(LogTemp, Log, TEXT("%s::SetCurrentDraft - creating fresh draft"), *GetName());
      CurrentDraft = NewObject<USoloDraft>();
    }
  }

//  if (AGarageLevelScriptActor* GarageLSA = Cast<AGarageLevelScriptActor>(GetWorld()->GetLevelScriptActor()))
//  {
//    UE_LOG(LogTemp, Log, TEXT("%s::SetCurrentDraft - GarageLSA ok"), *GetName());
//    if (ARobotCharacter* RobotChar = GarageLSA->GetRobotCharacter())
//    {
//      UE_LOG(LogTemp, Log, TEXT("%s::SetCurrentDraft - GarageLSA Char ok"), *GetName());
      if (CurrentDraft != nullptr)
      {
        RobotCharacter->SetPartAssignment(CurrentDraft->PartAssignment);
      }
//    }
//  }
}

void AGarageGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  UE_LOG(LogGameState, Log, TEXT("%s::EndPlay"), *GetName());
  if (UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>())
  {
    GameInstance->CurrentDraft = DuplicateObject<USoloDraft>(CurrentDraft, nullptr);
  }
  Super::EndPlay(EndPlayReason);
}

