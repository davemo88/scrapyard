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
      for (APlayerState* PlayerState : RobotPlayerState->Opponents)  
      {
        ARobotCharacter* OpponentRobotChar = PlayerState->GetPawn<ARobotCharacter>();
        bTargetAcquired = bTargetAcquired || IsTargetable(OpponentRobotChar);
//        UE_LOG(LogTemp, Warning, TEXT("Opponent Location: %s"), *PlayerState->GetPawn()->GetActorLocation().ToString());
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

