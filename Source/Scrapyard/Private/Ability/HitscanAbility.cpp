// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanAbility.h"

UHitscanAbility::UHitscanAbility()
{
  AbilityName = TEXT("HitscanAbility");
}

void UHitscanAbility::FireShot()
{
  UE_LOG(LogTemp, Warning, TEXT("UHitscanAbility::FireShot"));

  FHitResult OutHit;
  FireInstantHit(true, &OutHit);
}

void UHitscanAbility::FireInstantHit(bool bDealDamage, FHitResult* OutHit)
{
  UE_LOG(LogTemp, Warning, TEXT("UHitscanAbility::FireInstantHit"));

  const FVector SpawnLoc = GetFireStartLoc();
  const FRotator SpawnRot = GetBaseFireRotation();
  const FVector FireDirection = SpawnRot.Vector();
  const FVector EndTrace = SpawnLoc + FireDirection * 1000;

  FHitResult Hit;
  HitScanTrace(SpawnLoc, EndTrace, 0.0f, Hit, 0.0f);

  if (Hit.Actor != NULL && bDealDamage)
  {
    Hit.Actor->TakeDamage(1000.0f, )
  }
  if (OutHit != NULL)
  {
    *OutHit = Hit;
  }
}

