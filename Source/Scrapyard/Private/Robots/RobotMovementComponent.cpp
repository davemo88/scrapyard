// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotMovementComponent.h"
#include "GameFramework/Character.h"
#include "Player/RobotPlayerController.h"
#include "TimerManager.h"
#include "UnrealNetwork.h"

URobotMovementComponent::URobotMovementComponent()
{
// TODO: set all from robot stats
// slipperiness
  GroundFriction = 2.0f;
  BrakingDecelerationWalking = 555.0f;

  
// boosting
  BoostSpeedMultiplier = 2.0f;
  BoostAccelerationMultiplier = 2.0f;

  BoostHoldThresholdTime = 0.2f;

  bPrevBoostInput = false;
  bBoosting = false;

  MassNormalizer = 500.0f;
  LandingSpeedThreshold = -600.0f;
  LandingTime = 1.0f;

  SmoothLandingTime = 0.5f;

}

void URobotMovementComponent::BeginPlay()
{
  Super::BeginPlay();

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

  if (RobotChar != nullptr && RobotChar->HasAuthority())
  {
    UpdateRobotMovementState();
  }

}

void URobotMovementComponent::Landed(const FHitResult & Hit)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::Landed"), *GetName());
  UE_LOG(LogTemp, Warning, TEXT("Robot Velocity = %s"), *RobotChar->GetVelocity().ToString());
  if (RobotChar && RobotChar->GetVelocity().Z < LandingSpeedThreshold)
  {
    UE_LOG(LogTemp, Warning, TEXT("Rough Landing"));
    SetRobotMovementState(ERobotMovementState::MOVE_Land);
    RobotChar->GetWorldTimerManager().SetTimer(LandingTimerHandle, this, &URobotMovementComponent::OnLandingTimerExpired, LandingTime);
    if (RobotChar->GetController())
    {
      RobotChar->GetController()->SetIgnoreMoveInput(true);
    }
  }
  else if (RobotChar)
  {
    UE_LOG(LogTemp, Warning, TEXT("Smooth Landing"));
    RobotChar->GetWorldTimerManager().SetTimer(SmoothLandingTimerHandle, this, &URobotMovementComponent::OnSmoothLandingTimerExpired, SmoothLandingTime);
  }
}

void URobotMovementComponent::OnLandingTimerExpired()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnLandingTimerExpired"), *GetName());
//  MovementState = ERobotMovementState::MOVE_Walk;
  SetRobotMovementState(ERobotMovementState::MOVE_Walk);
  if (RobotChar != nullptr)
  {
    RobotChar->GetWorldTimerManager().ClearTimer(LandingTimerHandle);
    if (RobotChar->GetController())
    {
      RobotChar->GetController()->ResetIgnoreMoveInput();
    }
  }
}

void URobotMovementComponent::OnSmoothLandingTimerExpired()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnSmoothLandingTimerExpired"), *GetName());
  if (RobotChar != nullptr)
  {
    RobotChar->GetWorldTimerManager().ClearTimer(SmoothLandingTimerHandle);
  }
}

void URobotMovementComponent::UpdateRobotMovementState()
{
  if (RobotChar != nullptr)
  {
//    UE_LOG(LogTemp, Warning, TEXT("Beginning RobotMovementState: %i"), RobotMovementState);
    float Speed = RobotChar->GetVelocity().Size();
    if (IsWalking()) 
    {
//      UE_LOG(LogTemp, Warning, TEXT("anim instance char walking - speed %f"), Speed);
// if landing, wait for timer to run out
      if (RobotMovementState != ERobotMovementState::MOVE_Land)
      {
        if (Speed > 0.0f)
        {
          if (bBoosting)
          {
            SetRobotMovementState(ERobotMovementState::MOVE_Boost);
          }
          else
          {
            SetRobotMovementState(ERobotMovementState::MOVE_Walk);
          }
        }
        else
        {
//          UE_LOG(LogTemp, Warning, TEXT("anim instance setting MOVE_Idle %i"),ERobotMovementState::MOVE_Idle);
          SetRobotMovementState(ERobotMovementState::MOVE_Idle);
        }
      }
    }
    else if (IsFalling())
    {
      if (RobotMovementState != ERobotMovementState::MOVE_Land)
      {
        SetRobotMovementState(ERobotMovementState::MOVE_Fall);
      }
      else
      {
        UE_LOG(LogTemp, Warning, TEXT("landing while falling"));
      }
    }
    else if (IsFlying())
    {
      SetRobotMovementState(ERobotMovementState::MOVE_Fly);
    }
  }
//  UE_LOG(LogTemp, Warning, TEXT("Ending RobotMovementState: %i"), RobotMovementState);
}

ERobotMovementState URobotMovementComponent::GetRobotMovementState()
{
  return RobotMovementState;
}

void URobotMovementComponent::SetRobotMovementState(ERobotMovementState NewRobotMovementState)
{
  if (RobotChar != nullptr && RobotChar->HasAuthority())
  {
    RobotMovementState = NewRobotMovementState;
  }
}

void URobotMovementComponent::SetRobotChar(ARobotCharacter* NewRobotChar)
{
  RobotChar = NewRobotChar;
  UpdateFromRobotStats();
}

void URobotMovementComponent::UpdateFromRobotStats()
{
  if (RobotChar != nullptr)
  {
    GravityScale = MassNormalizer / float(RobotChar->RobotStats->Mass);
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
        if (SmoothLandingTimerHandle.IsValid())
        {
          StartBoosting();
        }
        else
        {
        UE_LOG(LogTemp, Warning, TEXT("%s::CheckBoostInput- Set Timer"), *GetName());
        Char->GetWorld()->GetTimerManager().SetTimer(BoostHoldTimerHandle, this, &URobotMovementComponent::BoostHoldTimerExpired, BoostHoldThresholdTime, false);
        }
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

  if (RobotMovementState == ERobotMovementState::MOVE_Boost)
  {
    SetRobotMovementState(ERobotMovementState::MOVE_Walk);
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
        Velocity.Z = JumpZVelocity/2.0f;
        SetMovementMode(MOVE_Flying); 
      }
//      else if (IsWalking())
//      {
//        
//      }

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
    if (IsFlying())
    {
      SetMovementMode(MOVE_Falling);
    }
    else if (IsWalking())
    {
//      SetRobotMovementState(ERobotMovementState::MOVE_Walk);
    }

    if (RobotChar->HasAuthority())
    {
      RobotChar->Power = FMath::Min(RobotChar->RobotStats->MaxPower, RobotChar->Power + 1);
    }
  }
}

float URobotMovementComponent::GetMaxSpeed() const
{
  float MaxSpeed = Super::GetMaxSpeed();

  MaxSpeed *=  MassNormalizer / float(RobotChar->RobotStats->Mass);

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

void URobotMovementComponent::GetLifetimeReplicatedProps(TArray <class FLifetimeProperty> & OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  DOREPLIFETIME(URobotMovementComponent, RobotMovementState);
}
