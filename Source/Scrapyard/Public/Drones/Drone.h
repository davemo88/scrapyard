// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Targeting/TargetableComponent.h"
#include "Targeting/TargetableInterface.h"
#include "Drone.generated.h"

UCLASS()
class SCRAPYARD_API ADrone : public AActor, public ITargetableInterface
{
  GENERATED_BODY()
  
public:  
  // Sets default values for this actor's properties
  ADrone();

// Called every frame
  virtual void Tick(float DeltaTime) override;

  virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

  virtual void BeginDestroy() override;

  UPROPERTY(EditAnywhere)
  int32 HitPoints;

  UPROPERTY(EditAnywhere)
  int32 Team;

  UPROPERTY()
  UTargetableComponent* TargetableComponent;

  UPROPERTY(EditAnywhere)
  UCapsuleComponent* CapsuleComponent;

  UPROPERTY(EditAnywhere)
  UStaticMeshComponent* StaticMeshComponent;

//  void OnDroneTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
  virtual void LifeSpanExpired() override;

// Targetable Interface
  virtual bool IsTargetableBy(ARobotCharacter* Robot) override;

  

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  void SetAssets();

  TSoftObjectPtr<UStaticMesh> StaticMesh;  
  TSoftObjectPtr<UMaterial> Material;

  UPROPERTY()
  UParticleSystem* OnDestroyParticleSystem; 
  UPROPERTY()
  UParticleSystem* OnHitParticleSystem; 

};
