// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotMovementComponent.h"
#include "GameFramework/Character.h"
#include "Player/RobotPlayerController.h"

void URobotMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
  Super::UpdateFromCompressedFlags(Flags);  
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
//      if (PC->HasDeferredFireInputs())
//      {
        PC->ApplyDeferredFireInputs();
//      }
    }
  }
}

class FNetworkPredictionData_Client* URobotMovementComponent::GetPredictionData_Client() const
{
  check(GetPawnOwner() != NULL);
  check(GetPawnOwner()->Role < ROLE_Authority);

  if (!ClientPredictionData)
  {
    URobotMovementComponent* MutableThis = const_cast<URobotMovementComponent*>(this);

    MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Robot(*this);
    MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
    MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
  }

  return ClientPredictionData;
}

void FSavedMove_Robot::Clear()
{
  Super::Clear();
}

uint8 FSavedMove_Robot::GetCompressedFlags() const
{
  uint8 Result = Super::GetCompressedFlags();

  return Result;
}

bool FSavedMove_Robot::CanCombineWith( const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const
{
  return Super::CanCombineWith(NewMove, Character, MaxDelta);
}

void FSavedMove_Robot::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character & ClientData)
{
  Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

  URobotMovementComponent* CharMov = Cast<URobotMovementComponent>(Character->GetCharacterMovement());
  if (CharMov)
  {

  }
}

void FSavedMove_Robot::PrepMoveFor(class ACharacter* Character)
{
  Super::PrepMoveFor(Character);

  URobotMovementComponent* CharMov = Cast<URobotMovementComponent>(Character->GetCharacterMovement());
  if (CharMov)
  {

  }

}

FNetworkPredictionData_Client_Robot::FNetworkPredictionData_Client_Robot(const UCharacterMovementComponent& ClientMovement) : Super(ClientMovement)
{

}
