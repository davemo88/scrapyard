// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotMovementComponent.h"
#include "Robots/RobotPlayerController.h"

URobotMovementComponent::URobotMovementComponent()
{

}
	
void URobotMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if (CharacterOwner != NULL)
  {
    ARobotPlayerController* PC = Cast<ARobotPlayerController>(CharacterOwner->Controller);
    if (PC != NULL && PC->PlayerInput != NULL)
    {
//      UE_LOG(LogTemp, Warning, TEXT("ApplyDeferred"));
      PC->ApplyDeferredFireInputs();
    }
  }
}

