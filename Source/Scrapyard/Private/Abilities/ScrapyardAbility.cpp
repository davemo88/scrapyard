// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrapyardAbility.h"
#include "Robots/RobotCharacter.h"
#include "Abilities/AbilityState.h"
#include "Abilities/AbilityStateActive.h"
#include "Abilities/AbilityStateInactive.h"
#include "Abilities/AbilityStateFiring.h"
#include "Player/RobotPlayerController.h"
#include "DrawDebugHelpers.h"
#include "UnrealNetwork.h"

AScrapyardAbility::AScrapyardAbility()
{
  AbilityName = TEXT("ScrapyardAbility");

  bReplicates = true;
  bAlwaysRelevant = true;

// TODO: virtual function to set up the ability states and targeting profile
  UE_LOG(LogTemp, Warning, TEXT("%s::AScrapyardAbility"), *GetName());
  SetupAbilityStates();
  CurrentState = ActiveState;

  SetupTargetingProfile();
}

void AScrapyardAbility::SetupAbilityStates()
{
  InactiveState = CreateDefaultSubobject<UAbilityStateInactive>(TEXT("AbilityStateInactive"));
  ActiveState = CreateDefaultSubobject<UAbilityStateActive>(TEXT("AbilityStateActive"));

  FiringState.Add(CreateDefaultSubobject<UAbilityStateFiring>(TEXT("FiringState0")));
  FireInterval.Add(1.0f);
}

void AScrapyardAbility::SetupTargetingProfile()
{
  TargetingProfile = CreateDefaultSubobject<UTargetingProfile>(TEXT("TargetingProfile"));
}

void AScrapyardAbility::StartFire(uint8 FireModeNum)
{
  UE_LOG(LogTemp,Warning,TEXT("%s::StartFire (Scrapyard Ability)"), *GetName());

  const UEnum* NetRoleEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"));
  UE_LOG(LogTemp, Warning, TEXT("%s::StartFire - Role: %s"), *GetName(), *(NetRoleEnum ? NetRoleEnum->GetNameStringByIndex(Role) : TEXT("oops")));
  UE_LOG(LogTemp, Warning, TEXT("%s::StartFire - RemoteRole: %s"), *GetName(), *(NetRoleEnum ? NetRoleEnum->GetNameStringByIndex(RobotOwner->GetRemoteRole()) : TEXT("oops")));

  bool bClientFired = BeginFiringSequence(FireModeNum, false);

  if (Role < ROLE_Authority)
  {
    UE_LOG(LogTemp,Warning,TEXT("%s::StartFire - Role < ROLE_Authority"), *GetName());
    UAbilityStateFiring* CurrentFiringState = FiringState.IsValidIndex(FireModeNum) ? FiringState[FireModeNum] : nullptr;  
    if (CurrentFiringState)
    {
      FireEventIndex++;
      if (FireEventIndex == 255)
      {
        FireEventIndex = 0;
      }
    }
    UE_LOG(LogTemp,Warning,TEXT("%s::StartFire - Calling ServerStartFire"), *GetName());
    ServerStartFire(FireModeNum, FireEventIndex, bClientFired);
  }
}

void AScrapyardAbility::StopFire(uint8 FireModeNum)
{
  UE_LOG(LogTemp,Warning,TEXT("%s::StopFire"), *GetName());
  EndFiringSequence(FireModeNum);
  if (Role < ROLE_Authority)
  {
    UAbilityStateFiring* CurrentFiringState = FiringState.IsValidIndex(FireModeNum) ? FiringState[FireModeNum] : nullptr;
    if (CurrentFiringState)
    {
      FireEventIndex++;
      if (FireEventIndex == 255)
      {
        FireEventIndex = 0;
      }
    }
    ServerStopFire(FireModeNum, FireEventIndex);
  }
}

void AScrapyardAbility::GotoState(UAbilityState* NewState)
{
  if (CurrentState != NewState)
  {
    UAbilityState* PrevState = CurrentState;
    if (CurrentState != NULL)
    {
      CurrentState->EndState();
    }
    if (CurrentState == PrevState)
    {
      CurrentState = NewState;
      CurrentState->BeginState(PrevState);

      StateChanged();
    }
  }
}

void AScrapyardAbility::GotoActiveState()
{
  GotoState(ActiveState);
}

void AScrapyardAbility::GotoFireMode(uint8 NewFireMode)
{
 UE_LOG(LogTemp,Warning,TEXT("%s::GotoFireMode"), *GetName());
 if (FiringState.IsValidIndex(NewFireMode))
 {
   CurrentFireMode = NewFireMode;
   GotoState(FiringState[NewFireMode]);
 }
}

bool AScrapyardAbility::BeginFiringSequence(uint8 FireModeNum, bool bClientFired)
{
  UE_LOG(LogTemp,Warning,TEXT("%s::BeginFiringSequence"), *GetName());
  if (RobotOwner != NULL)
  {
    RobotOwner->SetPendingFire(FireModeNum, true);
    if (FiringState.IsValidIndex(FireModeNum))
    {
      FiringState[FireModeNum]->PendingFireStarted();
    }
    bool bResult = CurrentState->BeginFiringSequence(FireModeNum, bClientFired);
    return bResult;
  }
  return false;
}

void AScrapyardAbility::EndFiringSequence(uint8 FireModeNum)
{
  UE_LOG(LogTemp,Warning,TEXT("%s::EndFiringSequence"), *GetName());
  if (RobotOwner)
  {
    RobotOwner->SetPendingFire(FireModeNum, false);
  }
  if (FiringState.IsValidIndex(FireModeNum))
  {
    FiringState[FireModeNum]->PendingFireStopped();
  }
  CurrentState->EndFiringSequence(FireModeNum);
}

bool AScrapyardAbility::WillSpawnShot(float DeltaTime)
{
  return (CurrentState != NULL) && CanFireAgain() && CurrentState->WillSpawnShot(DeltaTime);
}

bool AScrapyardAbility::CanFireAgain()
{
  return true;
}
  
void AScrapyardAbility::FireShot()
{
  UE_LOG(LogTemp, Warning, TEXT("AScrapyardAbility::FireShot"));
  // can either override this on ability subclasses
  // or override FireProjectile / FireInstantHit etc
}

bool AScrapyardAbility::IsFiring() const
{
  return CurrentState->IsFiring();
}

float AScrapyardAbility::GetRefireTime(uint8 FireModeNum)
{
  float RefireTime = 0.1f;

  if (FireInterval.IsValidIndex(FireModeNum))
  {
    RefireTime = FireInterval[FireModeNum];
  }

  return RefireTime;

}

void AScrapyardAbility::FireInstantHit(bool bDealDamage, FHitResult* OutHit)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::FireInstantHit"), *GetName());
}

FVector AScrapyardAbility::GetFireStartLoc(uint8 FireMode)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetFireStartLoc"), *GetName());
  if (FireMode == 255)
  {
    FireMode = CurrentFireMode;
  }
  if (RobotOwner == NULL)
  {
    return FVector::ZeroVector;
  }
  else
  {
    FVector BaseLoc = RobotOwner->GetActorLocation();
    return BaseLoc;
  }
}

FRotator AScrapyardAbility::GetBaseFireRotation()
{
  if (RobotOwner == NULL)
  {
    return FRotator::ZeroRotator;
  }
  else 
  {
    return RobotOwner->GetViewRotation();
  }
}

void AScrapyardAbility::HitScanTrace(const FVector& StartLocation, const FVector& EndTrace, float TraceRadius, FHitResult& Hit, float PredictionTime)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::HitScanTrace"), *GetName());
  const FName TraceTag("MyTraceTag");
  GetWorld()->DebugDrawTraceTag = TraceTag;

  ECollisionChannel TraceChannel = ECC_Pawn; 
  FCollisionQueryParams QueryParams(GetClass()->GetFName(), true, RobotOwner);
  QueryParams.TraceTag = TraceTag;
// single line trace
  if (TraceRadius <= 0.0f)
  {
    GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndTrace, TraceChannel, QueryParams);
    UE_LOG(LogTemp, Warning, TEXT("The Hit TraceStart is %s"), *Hit.TraceStart.ToString());
    if (Hit.Actor != NULL)
    {
      UE_LOG(LogTemp, Warning, TEXT("Hit an Actor!"));
    }
  }
  else
  {
    // this would be some kind of volume or surface
  }

//  if (!(Hit.Location - StartLocation).IsNearlyZero())
//  {
//    ARobotCharacter* ClientSideHitActor = (bTrackHitScanReplication && ReceivedHitScanHitChar && ((ReceivedHitScanIndex == FireEventIndex) || (ReceivedHitScanIndex == FireEventIndex - 1))) ? ReceivedHitScanHitChar ? nullptr;
//    ARobotCharacter* BestTarget = nullptr;
//    FVector BestPoint(0.f);
//    FVector BestCapsulePoint(0.f);
//    for (FConstPawnIterator Iterator = GetRobotOwner()->GetWorld()->GetPawnIterator() Iterator; ++Iterator)
//    {
//
//    }
//  }
}

void AScrapyardAbility::ServerStartFire_Implementation(uint8 FireModeNum, uint8 InFireEventIndex, bool bClientFired)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ServerStartFire_Implementation"), *GetName());

  BeginFiringSequence(FireModeNum, bClientFired);
}

bool AScrapyardAbility::ServerStartFire_Validate(uint8 FireModeNum, uint8 InFireEventIndex, bool bClientFired)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::ServerStartFire_Validate"), *GetName());
  return true;
}

void AScrapyardAbility::ServerStopFire_Implementation(uint8 FireModeNum, uint8 InFireEventIndex)
{
  EndFiringSequence(FireModeNum);
}

bool AScrapyardAbility::ServerStopFire_Validate(uint8 FireModeNum, uint8 InFireEventIndex)
{
  return true;
}

void AScrapyardAbility::ServerHitScanHit_Implementation(ARobotCharacter* HitScanChar, uint8 HitScanEventIndex)
{
  ReceivedHitScanHitChar = HitScanChar;
  ReceivedHitScanIndex = HitScanEventIndex;
}

bool AScrapyardAbility::ServerHitScanHit_Validate(ARobotCharacter* HitScanChar, uint8 HitScanEventIndex)
{
  return true;
}

void AScrapyardAbility::ClientMissedHitScan_Implementation(FVector_NetQuantize MissedHitScanStart, FVector_NetQuantize MissedHitScanEnd, FVector_NetQuantize MissedHitScanLoc, float MissedHitScanTime, uint8 MissedHitScanIndex)
{
  DrawDebugLine(GetWorld(), HitScanStart, HitScanEnd, FColor::Green, false, 8.f);                  
  DrawDebugLine(GetWorld(), MissedHitScanStart, MissedHitScanEnd, FColor::Yellow, false, 8.f);
  DrawDebugCapsule(GetWorld(), HitScanCharLoc, HitScanHeight, 40.f, FQuat::Identity, FColor::Green, false, 8.f);
  ARobotPlayerController* PC = GetRobotOwner() ? Cast<ARobotPlayerController>(GetRobotOwner()->GetController()) : nullptr;
  if (PC)
  {
//    PC->ClientSay(PC->UTPlayerState, FString::Printf(TEXT("HIT MISMATCH LOCAL index %d time %f      SERVER index %d time %f error distance %f"), HitScanIndex, HitScanTime, MissedHitScanIndex, MissedHitScanTime, (HitScanCharLoc - MissedHitScanLoc).Size()), ChatDestinations::System);  
  }
}

void AScrapyardAbility::GetLifetimeReplicatedProps(TArray <FLifetimeProperty > & OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);
  DOREPLIFETIME(AScrapyardAbility, RobotOwner);
//  DOREPLIFETIME(AScrapyardAbility, TargetingProfile);
}
