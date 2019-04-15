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

  bPrevBoostInput = false;
  bBoosting = false;

}

void URobotMovementComponent::BeginPlay()
{
  Super::BeginPlay();

  RobotChar = Cast<ARobotCharacter>(GetCharacterOwner());
}

void URobotMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
  Super::UpdateFromCompressedFlags(Flags);  

  bBoostInput = (Flags&FSavedMove_Character::FLAG_Custom_0) != 0;
}

void URobotMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  ARobotPlayerController* PC = Cast<ARobotPlayerController>(RobotChar->Controller);
  if (PC != NULL && PC->PlayerInput != NULL)
  {
//    this is from Unreal Tournament
//    UE_LOG(LogTemp, Warning, TEXT("ApplyDeferred"));
//    if (PC->HasDeferredFireInputs())
//    {
      PC->ApplyDeferredFireInputs();
//    }
  }
  
  CheckBoostInput();

  HandleBoosting();

  if (RobotChar)
  {
    float Pitch = RobotChar->GetViewRotation().Pitch;
//    UE_LOG(LogTemp, Warning, TEXT("%s View Rotation %s"), *GetName(), *RobotChar->GetViewRotation().ToString());
//    UE_LOG(LogTemp, Warning, TEXT("%s Rotation %s"), *GetName(), *RobotChar->GetActorRotation(.ToString());
    RobotChar->RobotTargetingComponent->SetRelativeRotation(FRotator(Pitch,0.0f,0.0f));
//    UE_LOG(LogTemp, Warning, TEXT("OurCamera Rel Rot: %s"), *RobotChar->OurCamera->RelativeRotation.ToString());
//    UE_LOG(LogTemp, Warning, TEXT("Camera Boom Rel Rot: %s"), *RobotChar->CameraBoom->RelativeRotation.ToString());
  }

}

void URobotMovementComponent::SetBoostInput(uint8 bNewBoostInput)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetBoostInput"), *GetName());
  bBoostInput = bNewBoostInput; 
}

void URobotMovementComponent::CheckBoostInput()
{
  if (ACharacter* Char = GetCharacterOwner())
  {
    if (!bBoosting && bBoostInput && !bPrevBoostInput && !BoostHoldTimerHandle.IsValid())
    {
      if (IsWalking())
      {
        UE_LOG(LogTemp, Warning, TEXT("%s::CheckBoostInput- Set Timer"), *GetName());
        Char->GetWorld()->GetTimerManager().SetTimer(BoostHoldTimerHandle, this, &URobotMovementComponent::BoostHoldTimerExpired, BoostHoldThresholdTime, false);

      }
      else if (IsFalling())
      {
        StartBoosting();
      }
    }
    else if (!bBoostInput)
    {
      if (BoostHoldTimerHandle.IsValid() && (Char->GetWorld()->GetTimerManager().GetTimerElapsed(BoostHoldTimerHandle) < BoostHoldThresholdTime))
      {
        UE_LOG(LogTemp, Warning, TEXT("%s::SetBoosting - Jump"), *GetName());
        Char->GetWorld()->GetTimerManager().ClearTimer(BoostHoldTimerHandle);
        DoJump(true);
      }
      else 
      {
        StopBoosting();
      }
    }

    bPrevBoostInput = bBoostInput;
  }
}

void URobotMovementComponent::ClearBoostInput()
{

}


void URobotMovementComponent::BoostHoldTimerExpired()
{ 
  UE_LOG(LogTemp, Warning, TEXT("%s::BoostHoldTimerExpired"), *GetName());
  if (ACharacter* Char = GetCharacterOwner())
  {
    Char->GetWorld()->GetTimerManager().ClearTimer(BoostHoldTimerHandle);
    StartBoosting();
  }
}

void URobotMovementComponent::StartBoosting()
{
  bBoosting = true;
}

void URobotMovementComponent::StopBoosting()
{
  bBoosting = false;
  if (IsFlying())
  {
    SetMovementMode(MOVE_Falling);
  }
}

void URobotMovementComponent::HandleBoosting()
{
  if (bBoosting)
  {
// TODO: clean up management of replicated Power variable. should this be in the movement component at all?

    if (RobotChar->Power > 0)
    {
// handle boosting cases
      if (IsFlying() || IsFalling())
      {
// TODO: boost velocity should depend on robot stats
        Velocity.Z = JumpZVelocity;
        SetMovementMode(MOVE_Flying); 
      }

      if (RobotChar->HasAuthority())
      {
        RobotChar->Power = FMath::Max(0, RobotChar->Power - RobotChar->RobotStats->BoosterPowerDrain);
      }

    }
    else
    {
      StopBoosting();
    }
  }
  else
  {
    if (RobotChar->HasAuthority())
    {
      RobotChar->Power = FMath::Min(RobotChar->RobotStats->MaxPower, RobotChar->Power + 5);
    }
  }

}

float URobotMovementComponent::GetMaxSpeed() const
{
  float MaxSpeed = Super::GetMaxSpeed();

//  MaxSpeed *= 100.0f/float(RobotChar->RobotStats->Mass);

  if (bBoosting)
  {
//    UE_LOG(LogTemp, Warning, TEXT("%s::GetMaxSpeed - Boost"), *GetName());
    MaxSpeed *= BoostSpeedMultiplier;
  }

  return MaxSpeed;
}

float URobotMovementComponent::GetMaxAcceleration() const
{
  float MaxAcceleration = Super::GetMaxAcceleration();

  if (bBoosting)
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

  bSavedBoostInput = 0;
}

uint8 FSavedMove_Robot::GetCompressedFlags() const
{
  uint8 Result = Super::GetCompressedFlags();

//TODO: what's the deal with FLAG_Custom_0
  if (bSavedBoostInput)
  {
    Result |= FLAG_Custom_0;
  }

  return Result;
}

bool FSavedMove_Robot::CanCombineWith( const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const
{
  if (bSavedBoostInput != ((FSavedMove_Robot*)&NewMove)->bSavedBoostInput)
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
    bSavedBoostInput = CharMov->bBoostInput;
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

