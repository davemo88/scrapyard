// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanAbility.h"
#include "Targeting/RectangularTargetingProfile.h"
#include "DrawDebugHelpers.h"
#include "Projectiles/LaserProjectile.h"
#include "Robots/RobotCharacter.h"

AHitscanAbility::AHitscanAbility()
{
  AbilityName = TEXT("HitscanAbility");
  AbilityRange = 3000;
//  SetActorTickEnabled(false);

  InstantHitInfo.Add(FInstantHitDamageInfo());
}

void AHitscanAbility::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  UE_LOG(LogTemp, Warning, TEXT("%s::Tick"), *GetName());
}

void AHitscanAbility::BeginPlay()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay - Location:"), *GetName(), *GetActorLocation().ToString());
}

void AHitscanAbility::FireShot()
{
  UE_LOG(LogTemp, Warning, TEXT("AHitscanAbility::FireShot"));

  FHitResult OutHit;
  FireInstantHit(true, &OutHit);
}

void AHitscanAbility::FireInstantHit(bool bDealDamage, FHitResult* OutHit)
{
  UE_LOG(LogTemp, Warning, TEXT("AHitscanAbility::FireInstantHit"));

//TODO: replace these with output from targeting system
//  const FVector SpawnLoc = GetFireStartLoc();
//  const FRotator SpawnRot = GetBaseFireRotation();
//  const FVector FireDirection = SpawnRot.Vector();
//  const FVector EndTrace = SpawnLoc + FireDirection * AbilityRange;
  FAbilityEffectParams AbilityEffectParams;
  FHitResult Hit;
  FVector FireDirection;
  const FVector FireLoc = RobotOwner->GetActorLocation() + RobotOwner->RobotBodyComponent->GetComponentRotation().RotateVector(FVector(-70,220,70));

//TODO: do this laser in a multicast function
//TODO: refactor trace end point so this can go more smoothly
//  ALaserProjectile* Laser = GetWorld()->SpawnActor<ALaserProjectile>(FActorSpawnParameters());
//  Laser->SetLifeSpan(0.5f);
//  Laser->LaserBeam->SetBeamSourcePoint(0,FireLoc,0);

  if (RobotOwner->RobotTargetingComponent->IsTargetAcquired())
  {
    AActor* Target = RobotOwner->RobotTargetingComponent->GetTargets()[0];
    const FVector PredictedLoc = RobotOwner->RobotTargetingComponent->GetPredictedTargetLocation(Target, 0.0f);
    FireDirection = (PredictedLoc - FireLoc).GetSafeNormal();
  }
  else
  {
    FireDirection = RobotOwner->GetViewRotation().Vector(); 
  }

  const FVector EndLoc = FireLoc + FireDirection * AbilityRange;

  AbilityEffectParams.FireLoc = FireLoc;
  AbilityEffectParams.EndLoc = EndLoc;

  UE_LOG(LogTemp, Warning, TEXT("FireLoc: %s, EndLoc: %s"), *AbilityEffectParams.FireLoc.ToString(), *AbilityEffectParams.EndLoc.ToString());

  HitScanTrace(FireLoc, EndLoc, 0.0f, Hit, 0.0f);

  if (Hit.Actor != NULL && bDealDamage)
  {
    Hit.Actor->TakeDamage(
        InstantHitInfo[CurrentFireMode].Damage,
        FScrapyardPointDamageEvent(
          InstantHitInfo[CurrentFireMode].Damage,
          Hit,
          FVector::ZeroVector,
          InstantHitInfo[CurrentFireMode].DamageType,
          FVector::ZeroVector),
        RobotOwner->Controller,
        this);
  }
  if (OutHit != NULL)
  {
    *OutHit = Hit;
  }

  MulticastShowAbilityEffects(AbilityEffectParams);

}

void AHitscanAbility::SetupTargetingProfile()
{
  TargetingProfile = CreateDefaultSubobject<URectangularTargetingProfile>(TEXT("TargetingProfile"));
}

void AHitscanAbility::ShowAbilityEffects(FAbilityEffectParams AbilityEffectParams)
{
//  const FVector FireLoc = RobotOwner->GetActorLocation() + RobotOwner->RobotBodyComponent->GetComponentRotation().RotateVector(FVector(-70,220,70));
//  const FVector EndLoc = FireLoc + AbilityEffectParams.FireDirection * AbilityRange;
  UE_LOG(LogTemp, Warning, TEXT("FireLoc: %s, EndLoc: %s"), *AbilityEffectParams.FireLoc.ToString(), *AbilityEffectParams.EndLoc.ToString());
  ALaserProjectile* Laser = GetWorld()->SpawnActor<ALaserProjectile>(FActorSpawnParameters());
  Laser->SetLifeSpan(0.5f);
  Laser->LaserBeam->SetBeamSourcePoint(0,AbilityEffectParams.FireLoc,0);
  Laser->LaserBeam->SetBeamTargetPoint(0,AbilityEffectParams.EndLoc,0);

}
