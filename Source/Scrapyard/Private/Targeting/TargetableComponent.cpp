// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetableComponent.h"
#include "Scrapyard.h"
#include "Game/RobotGameState.h"


// Sets default values for this component's properties
UTargetableComponent::UTargetableComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  // ...
}


// Called when the game starts
void UTargetableComponent::BeginPlay()
{
  Super::BeginPlay();

  RegisterWithGamestate();
}

void UTargetableComponent::BeginDestroy()
{
  UnregisterWithGamestate();

  Super::BeginDestroy();
}



// Called every frame
void UTargetableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // ...
}

void UTargetableComponent::RegisterWithGamestate()
{
  if (GetOwner() && GetOwner()->HasAuthority() && GetOwner()->GetWorld())
  {
    if (ARobotGameState* RobotGameState = GetOwner()->GetWorld()->GetGameState<ARobotGameState>())
    {
      RobotGameState->AddTargetable(GetOwner());
    }
  }
}

void UTargetableComponent::UnregisterWithGamestate()
{
  UE_LOG(LogTargeting, Log, TEXT("%s::UnregisterWithGamestate"), *GetName());
  if (GetOwner() && GetOwner()->HasAuthority() && GetOwner()->GetWorld())
  {
    if (ARobotGameState* RobotGameState = GetOwner()->GetWorld()->GetGameState<ARobotGameState>())
    {
      RobotGameState->RemoveTargetable(GetOwner());
    }
  }
}
