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

  ARobotCharacter* RobotChar = Cast<ARobotCharacter>(GetOwner());

  if (RobotChar->HasAuthority() && (RobotChar->GetController() != nullptr))
  {
    ARobotPlayerState* RobotPlayerState = RobotChar->GetController()->GetPlayerState<ARobotPlayerState>();
    if (RobotPlayerState)
    {
      bTargetAcquired = false;
//      for (APlayerState* PlayerState : RobotPlayerState->Opponents)  
      for (TActorIterator<ARobotCharacter> ActorItr(RobotChar->GetWorld()); ActorItr; ++ActorItr)
      {
        ARobotCharacter* OtherChar = *ActorItr;
        if (OtherChar != RobotChar)
        {
//          ARobotCharacter* OpponentRobotChar = PlayerState->GetPawn<ARobotCharacter>();
          bTargetAcquired = bTargetAcquired || IsTargetable(OtherChar);
//          UE_LOG(LogTemp, Warning, TEXT("Opponent Location: %s"), *PlayerState->GetPawn()->GetActorLocation().ToString());
          UE_LOG(LogTemp, Warning, TEXT("Opponent Location: %s"), *OtherChar->GetActorLocation().ToString());
        }
      }
    }
  }

}

bool URobotTargetingComponent::IsTargetAcquired()
{
  return bTargetAcquired;
}

bool URobotTargetingComponent::IsTargetable(AActor* OtherActor)
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
