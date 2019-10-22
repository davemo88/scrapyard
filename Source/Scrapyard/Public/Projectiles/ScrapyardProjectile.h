// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Robots/RobotCharacter.h"
#include "ScrapyardProjectile.generated.h"

UCLASS()
class SCRAPYARD_API AScrapyardProjectile : public AActor
{
  GENERATED_BODY()
  
public:  
  // Sets default values for this actor's properties
  AScrapyardProjectile();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

  UPROPERTY()
  ARobotCharacter* RobotOwner;

  virtual void Fire(FVector FireDirection);

protected:

//  UPROPERTY(EditAnywhere)
//  UProjectileMovementComponent* ProjectileMovementComponent;

  UPROPERTY(EditAnywhere)
  UCapsuleComponent* CapsuleComponent;

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

//TODO: why reliable?
  UFUNCTION(NetMulticast, Unreliable)
  void MulticastPlayOnDestroyEffects();

  virtual void PlayOnDestroyEffects();

  UPROPERTY()
  float ProjectileSpeed = 1000.0f;

  UPROPERTY()
  float ProjectileLifeSpan = 1.0f;
  
};
