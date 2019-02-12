// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanAbility.h"
#include "Robots/RobotCharacter.h"

AHitscanAbility::AHitscanAbility()
{
  AbilityName = TEXT("HitscanAbility");

  InstantHitInfo.Add(FInstantHitDamageInfo());
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

  const FVector SpawnLoc = GetFireStartLoc();
  const FRotator SpawnRot = GetBaseFireRotation();
  const FVector FireDirection = SpawnRot.Vector();
  const FVector EndTrace = SpawnLoc + FireDirection * 1000;

  FHitResult Hit;
  HitScanTrace(SpawnLoc, EndTrace, 0.0f, Hit, 0.0f);

  if (Hit.Actor != NULL && bDealDamage)
  {
    Hit.Actor->TakeDamage(
        InstantHitInfo[CurrentFireMode].Damage,
        FScrapyardPointDamageEvent(
          InstantHitInfo[CurrentFireMode].Damage,
          Hit,
          FireDirection,
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

