// Fill out your copyright notice in the Description page of Project Settings.

#include "SoloDraftActor.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "UObjectGlobals.h"
#include "ScrapyardGameInstance.h"
#include "SoloDraft.h"
#include "HeadPart.h"
#include "CorePart.h"
#include "ArmsPart.h"
#include "LegsPart.h"
#include "RobotPartActor.h"
#include "Parts/Head/HeadPart_Default.h"
#include "Parts/Core/CorePart_Default.h"
#include "Parts/Arms/ArmsPart_Default.h"
#include "Parts/Legs/LegsPart_Default.h"
#include "Parts/Handheld/HandheldPart_Default.h"
#include "Player/SoloDraftPlayerController.h"


// Sets default values
ASoloDraftActor::ASoloDraftActor()
{
   // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  
  CurrentDraft = CreateDefaultSubobject<USoloDraft>(TEXT("CurrentDraft"));

}

// Called when the game starts or when spawned
void ASoloDraftActor::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("ASoloDraftActor::BeginPlay"));
  Super::BeginPlay();

  HeadParts.Add(NewObject<UHeadPart_Default>());
  CoreParts.Add(NewObject<UCorePart_Default>()); 
  ArmsParts.Add(NewObject<UArmsPart_Default>()); 
  LegsParts.Add(NewObject<ULegsPart_Default>());

  SpawnDraftCamera();

  ASoloDraftPlayerController* PC = Cast<ASoloDraftPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

  NextPackReady.AddDynamic(PC, &ASoloDraftPlayerController::OnNextPack);

  NextPack();

}

// Called every frame
void ASoloDraftActor::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

void ASoloDraftActor::SpawnDraftCamera()
{
  UWorld* World = GetWorld();
  ACameraActor* DraftCamera = World->SpawnActor<ACameraActor>(FVector(-420.0f, 0.0f, 200.0f), FRotator(0.0f, 0.0f, 0.0f), FActorSpawnParameters());
  World->GetFirstPlayerController()->SetViewTarget(DraftCamera);
}

ARobotPartActor* ASoloDraftActor::SpawnRobotPartActor(URobotPart* RobotPart, FVector Loc, FRotator Rot, FActorSpawnParameters SpawnParams)
{
  UWorld* World = GetWorld();
  ARobotPartActor* RobotPartActor = World->SpawnActor<ARobotPartActor>(Loc, Rot, SpawnParams);
  RobotPartActor->SetRobotPart(RobotPart);
  RobotPartActor->OnRobotPartClicked.AddDynamic(this, &ASoloDraftActor::DraftPart);
  return RobotPartActor;
}

void ASoloDraftActor::SpawnPartCards()
{
  FRotator Rot = FRotator(0.f, 180.f, 0.f);
  for (int32 i = 0; i < CurrentDraft->CurrentPack.Num(); ++i)
  {
    float YVal = FMath::Pow(-1,i) * 100.f; 
//    float ZVal = FMath::Pow(-1,i) * 50.f + 250.f;
    float ZVal = (i < (CurrentDraft->CurrentPack.Num()/2)) ? 200.f : 300.f;
    PartActors.Add(SpawnRobotPartActor(CurrentDraft->CurrentPack[i],FVector(0,YVal,ZVal),Rot));
  }
}

void ASoloDraftActor::DestroyPartCards()
{
  PartActors.Empty();
}

void ASoloDraftActor::NextPack()
{
  DestroyPartCards();
  SamplePack();
  SpawnPartCards();
  NextPackReady.Broadcast();
}

void ASoloDraftActor::SamplePack()
{
//  if (Role == ROLE_Authority)
//  {
  CurrentDraft->CurrentPack.Empty();
  CurrentDraft->CurrentPack.Add(SamplePart<UHeadPart>(HeadParts));
  CurrentDraft->CurrentPack.Add(SamplePart<UCorePart>(CoreParts));
  CurrentDraft->CurrentPack.Add(SamplePart<UArmsPart>(ArmsParts));
  CurrentDraft->CurrentPack.Add(SamplePart<ULegsPart>(LegsParts));
//  }

}

template<typename T>
T* ASoloDraftActor::SamplePart(TArray<T*>& Parts, bool Replacement)
{
  int32 NumParts = Parts.Num();
  T* RobotPart = nullptr;
  if (NumParts > 0)
  {
    int Index = FMath::RandRange(0, NumParts - 1);
    RobotPart = Parts[Index];
    if (!Replacement)
    {
      Parts.RemoveAt(Index);
    }
  }
  return RobotPart;
}

void ASoloDraftActor::DraftPart(URobotPart* RobotPart)
{
//  UE_LOG(LogTemp, Warning, TEXT("drafting %s"), *RobotPart->PartName);
  UE_LOG(LogTemp, Warning, TEXT("drafting a part"));
  CurrentDraft->Picks++;
  RobotPart->Draft(CurrentDraft);

  UE_LOG(LogTemp, Warning, TEXT("num heads %i"), CurrentDraft->DraftedHeads.Num());
  UE_LOG(LogTemp, Warning, TEXT("num cores %i"), CurrentDraft->DraftedCores.Num());
  UE_LOG(LogTemp, Warning, TEXT("num arms %i"), CurrentDraft->DraftedArms.Num());
  UE_LOG(LogTemp, Warning, TEXT("num legs %i"), CurrentDraft->DraftedLegs.Num());

  if (CurrentDraft->Picks < CurrentDraft->MaxPicks)
  {
    NextPack();
  }
  else
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
    if (CurrentDraft != nullptr)
    {
      UE_LOG(LogTemp, Warning, TEXT("draft complete"));
      GameInstance->SoloDraft = DuplicateObject(CurrentDraft, NULL);
      UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/GarageLevel");
    }
  }
}
