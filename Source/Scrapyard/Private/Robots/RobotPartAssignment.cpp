// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartAssignment.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "Parts/Heads/HeadPart_Default.h"

bool URobotPartAssignment::IsComplete()
{
  return (Head != nullptr && Core != nullptr && Arms != nullptr && Legs != nullptr);
}

void URobotPartAssignment::UnassignAll()
{
  Head = nullptr;
  Core = nullptr;
  Arms = nullptr;
  Legs = nullptr;
  RightHandheld = nullptr;
}

void URobotPartAssignment::SetDefaultAssignment()
{
  UWorld* World = GetWorld();
  if (World)
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(World->GetGameInstance());
//    Head = GameInstance->DefaultAssetsBP->DefaultHeadPart;
    Core = GameInstance->DefaultAssetsBP->DefaultCorePart;
    Arms = GameInstance->DefaultAssetsBP->DefaultArmsPart;
    Legs = GameInstance->DefaultAssetsBP->DefaultLegsPart;
    RightHandheld = GameInstance->DefaultAssetsBP->DefaultHandheldPart;
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("World was null for default assignemnt"));
  }

  Head = NewObject<UHeadPart_Default>();
  if (Head)
  {
    
    UE_LOG(LogTemp, Warning, TEXT("HeadPart is %s"), *Head->PartName);
  }
}
