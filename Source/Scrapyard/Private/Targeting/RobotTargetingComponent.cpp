// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotTargetingComponent.h"
#include "Player/RobotPlayerController.h"
#include "Player/RobotPlayerState.h"
#include "Robots/RobotCharacter.h"
#include "Engine.h"


// Sets default values for this component's properties
URobotTargetingComponent::URobotTargetingComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  bTargetAcquired = false;

  Range = 0.f;

}


// Called when the game starts
void URobotTargetingComponent::BeginPlay()
{
  Super::BeginPlay();

  // ...
  
}


// Called every frame
void URobotTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

//  ARobotCharacter* RobotChar = Cast<ARobotCharacter>(GetOwner());
//
//  if (RobotChar->HasAuthority() && (RobotChar->GetController() != nullptr))
//  {
//    ARobotPlayerState* RobotPlayerState = RobotChar->GetController()->GetPlayerState<ARobotPlayerState>();
//    if (RobotPlayerState)
//    {
//      bTargetAcquired = false;
////      for (APlayerState* PlayerState : RobotPlayerState->Opponents)  
////      for (TActorIterator<ARobotCharacter> ActorItr(RobotChar->GetWorld()); ActorItr; ++ActorItr)
//      for (AActor Targetable : Targetables)
//      {
//        ARobotCharacter* OtherChar = *ActorItr;
//        if (OtherChar != RobotChar)
//        {
////          ARobotCharacter* OpponentRobotChar = PlayerState->GetPawn<ARobotCharacter>();
//          bTargetAcquired = bTargetAcquired || IsTargetable(OtherChar);
////          UE_LOG(LogTemp, Warning, TEXT("Opponent Location: %s"), *PlayerState->GetPawn()->GetActorLocation().ToString());
////          UE_LOG(LogTemp, Warning, TEXT("Opponent Location: %s"), *OtherChar->GetActorLocation().ToString());
//        }
//      }
//    }
//  }
  
  bTargetAcquired = false;
  for (AActor* Targetable : Targetables)
  {
    bTargetAcquired = bTargetAcquired || IsTargeted(Targetable);
  }
}

bool URobotTargetingComponent::IsTargetAcquired()
{
  return bTargetAcquired;
}

bool URobotTargetingComponent::IsTargeted(AActor* OtherActor)
{
  return false;
}

float URobotTargetingComponent::GetRange()
{
  return Range;
}

TArray<FVector> URobotTargetingComponent::InitFaceVerts()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::InitFaceVerts"), *GetName());
  TArray<FVector> FaceVerts;
  FaceVerts.Add(FVector(GetRange(),0,0));
  return FaceVerts;
}

TArray<FVector> URobotTargetingComponent::GetFaceVerts()
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::GetFaceVerts"), *GetName());
  static TArray<FVector> FaceVerts = InitFaceVerts();
  return FaceVerts;
}

void URobotTargetingComponent::AddTargetable(AActor* Targetable)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::AddTargetable"), *GetName());
  UE_LOG(LogTemp, Warning, TEXT("%s::AddTargetable - %s"), *GetName(), *Targetable->GetName());
  Targetables.Add(Targetable);
}

void URobotTargetingComponent::RemoveTargetable(AActor* Targetable)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::RemoveTargetable"), *GetName());
  Targetables.Remove(Targetable);
}

bool URobotTargetingComponent::IsTargetable(AActor* Actor)
{
  ARobotCharacter* OwnerChar = Cast<ARobotCharacter>(GetOwner());
  if (ARobotCharacter* OtherChar = Cast<ARobotCharacter>(Actor))
  {
    if (OwnerChar->Team != OtherChar->Team)
    {
      return true; 
    }
  }

  return false;
}

