// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotMovementComponent.h"
#include "GameFramework/Character.h"
#include "Player/RobotPlayerController.h"
#include "TimerManager.h"

URobotMovementComponent::URobotMovementComponent()
{
// slipperiness
// TODO: depends on leg part
  GroundFriction = 2.0f;
  BrakingDecelerationWalking = 555.0f;

// boosting
// TODO: depends on core part, weight 
  BoostSpeedMultiplier = 2.0f;
  BoostAccelerationMultiplier = 2.0f;

  BoostHoldThresholdTime = 0.2f;
}

void URobotMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
  Super::UpdateFromCompressedFlags(Flags);  

  bWantsToBoost = (Flags&FSavedMove_Character::FLAG_Custom_0) != 0;
}

void URobotMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if (CharacterOwner != NULL)
  {
    ARobotPlayerController* PC = Cast<ARobotPlayerController>(CharacterOwner->Controller);
    if (PC != NULL && PC->PlayerInput != NULL)
    {
//      this is from Unreal Tournament
//      UE_LOG(LogTemp, Warning, TEXT("ApplyDeferred"));
//      if (PC->HasDeferredFireInputs())
//      {
        PC->ApplyDeferredFireInputs();
//      }
    }
  }
}

void URobotMovementComponent::SetBoosting(uint8 bBoosting)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetBoosting"), *GetName());
  bWantsToBoost = bBoosting; 
  if (ACharacter* Char = GetCharacterOwner())
  {
    if (bBoosting && !BoostHoldTimerHandle.IsValid())
    {
      UE_LOG(LogTemp, Warning, TEXT("%s::SetBoosting - Set Timer"), *GetName());
      Char->GetWorld()->GetTimerManager().SetTimer(BoostHoldTimerHandle, this, &URobotMovementComponent::BoostHoldTimerExpired, BoostHoldThresholdTime, false);
    }
    else if (!bBoosting && BoostHoldTimerHandle.IsValid() && (Char->GetWorld()->GetTimerManager().GetTimerElapsed(BoostHoldTimerHandle) < BoostHoldThresholdTime))
    {
      UE_LOG(LogTemp, Warning, TEXT("%s::SetBoosting - Jump"), *GetName());
  UE_LOG(LogTemp, Warning, TEXT("%s::SetBoosting"), *GetName());
      Char->GetWorld()->GetTimerManager().ClearTimer(BoostHoldTimerHandle);
      DoJump(true);
    }
  }
}

void URobotMovementComponent::BoostHoldTimerExpired()
{ 
  UE_LOG(LogTemp, Warning, TEXT("%s::BoostHoldTimerExpired"), *GetName());
  if (ACharacter* Char = GetCharacterOwner())
  {
    Char->GetWorld()->GetTimerManager().ClearTimer(BoostHoldTimerHandle);
  }
}

float URobotMovementComponent::GetMaxSpeed() const
{
  float MaxSpeed = Super::GetMaxSpeed();

  if (bWantsToBoost)
  {
//    UE_LOG(LogTemp, Warning, TEXT("%s::GetMaxSpeed - Boost"), *GetName());
    MaxSpeed *= BoostSpeedMultiplier;
  }

  return MaxSpeed;
}

float URobotMovementComponent::GetMaxAcceleration() const
{
  float MaxAcceleration = Super::GetMaxAcceleration();

  if (bWantsToBoost)
  {
//    UE_LOG(LogTemp, Warning, TEXT("%s::GetMaxAcceleration - Boost"), *GetName());
    MaxAcceleration *= BoostAccelerationMultiplier;
  }

  return MaxAcceleration;
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

  bSavedWantsToBoost = 0;
}

uint8 FSavedMove_Robot::GetCompressedFlags() const
{
  uint8 Result = Super::GetCompressedFlags();

//TODO: what's the deal with FLAG_Custom_0
  if (bSavedWantsToBoost)
  {
    Result |= FLAG_Custom_0;
  }

  return Result;
}

bool FSavedMove_Robot::CanCombineWith( const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const
{
  if (bSavedWantsToBoost != ((FSavedMove_Robot*)&NewMove)->bSavedWantsToBoost)
  {
    return false;
  }

  return Super::CanCombineWith(NewMove, Character, MaxDelta);
}

void FSavedMove_Robot::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character & ClientData)
{
  Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

  URobotMovementComponent* CharMov = Cast<URobotMovementComponent>(Character->GetCharacterMovement());
  if (CharMov)
  {
    bSavedWantsToBoost = CharMov->bWantsToBoost;
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

FSavedMovePtr FNetworkPredictionData_Client_Robot::AllocateNewMove()
{
  return FSavedMovePtr(new FSavedMove_Robot()); 
}

