// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "ScrapyardDamageType.generated.h"

USTRUCT()
struct FScrapyardPointDamageEvent : public FPointDamageEvent
{
  GENERATED_BODY()

  FScrapyardPointDamageEvent()
  : FPointDamageEvent()
  {}
  FScrapyardPointDamageEvent(float InDamage, const FHitResult& InHitInfo, const FVector& InShotDirection, TSubclassOf<UDamageType> InDamageTypeClass, const FVector& InMomentum = FVector::ZeroVector)
  : FPointDamageEvent(InDamage, InHitInfo, InShotDirection, InDamageTypeClass), Momentum(InMomentum)
  {}

  UPROPERTY()
  FVector Momentum;

  static const int32 ClassID = 101;
  virtual int32 GetTypeID() const { return FScrapyardPointDamageEvent::ClassID; };
  virtual bool IsOfType(int32 InID) const { return (FScrapyardPointDamageEvent::ClassID == InID) || FPointDamageEvent::IsOfType(InID); };

};

USTRUCT()
struct FScrapyardRadialDamageEvent : public FRadialDamageEvent
{
  GENERATED_BODY()

  FScrapyardRadialDamageEvent()
  : FRadialDamageEvent(), bScaleMomentum(true)
  {}

  UPROPERTY()
  FVector_NetQuantizeNormal ShotDirection;

  UPROPERTY()
  FVector BaseMomentumMagnitude;
  UPROPERTY()
  bool bScaleMomentum;

  static const int32 ClassID = 101;
  virtual int32 GetTypeID() const { return FScrapyardRadialDamageEvent::ClassID; };
  virtual bool IsOfType(int32 InID) const { return (FScrapyardRadialDamageEvent::ClassID == InID) || FRadialDamageEvent::IsOfType(InID); };

};
/**
 * 
 */
UCLASS()
class SCRAPYARD_API UScrapyardDamageType : public UDamageType
{
  GENERATED_BODY()

};
