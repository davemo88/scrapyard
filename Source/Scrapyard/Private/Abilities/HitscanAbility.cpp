// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanAbility.h"
#include "Targeting/RectangularTargetingProfile.h"
#include "DrawDebugHelpers.h"
#include "Projectiles/LaserProjectile.h"
#include "Robots/RobotCharacter.h"

AHitscanAbility::AHitscanAbility()
{
  AbilityName = TEXT("HitscanAbility");
  AbilityRange = 1000;
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

  FHitResult Hit;
  const FVector RobotLoc = RobotOwner->GetActorLocation() + RobotOwner->RobotBodyComponent->GetComponentRotation().RotateVector(FVector(-70,220,70));
//TODO: do this laser in a multicast function
//TODO: refactor trace end point so this can go more smoothly
  ALaserProjectile* Laser = GetWorld()->SpawnActor<ALaserProjectile>(FActorSpawnParameters());
  Laser->SetLifeSpan(2.0f);
  Laser->LaserBeam->SetBeamSourcePoint(0,RobotLoc,0);
  if (RobotOwner->RobotTargetingComponent->IsTargetAcquired())
  {
    AActor* Target = RobotOwner->RobotTargetingComponent->GetTargets()[0];
    const FVector PredictedLoc = RobotOwner->RobotTargetingComponent->GetPredictedTargetLocation(Target, 0.0f);
    Laser->LaserBeam->SetBeamTargetPoint(0,PredictedLoc,0);
    HitScanTrace(RobotLoc, PredictedLoc, 0.0f, Hit, 0.0f);
  }
  else
  {
    const FVector ViewDirection = RobotOwner->GetViewRotation().Vector(); 
    const FVector EndLoc = RobotLoc + ViewDirection * AbilityRange;
    Laser->LaserBeam->SetBeamTargetPoint(0,EndLoc,0);
    HitScanTrace(RobotLoc, EndLoc, 0.0f, Hit, 0.0f);
  }

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
}

void AHitscanAbility::SetupTargetingProfile()
{
  TargetingProfile = CreateDefaultSubobject<URectangularTargetingProfile>(TEXT("TargetingProfile"));
}
