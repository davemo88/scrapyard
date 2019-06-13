// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Robots/RobotBodyComponent.h"
#include "Robots/RobotStats.h"
#include "Robots/RobotTargetingComponent.h"
#include "Parts/PartAssignment.h"
#include "Targeting/TargetableComponent.h"
#include "Targeting/TargetableInterface.h"
#include "Abilities/ScrapyardAbility.h"
#include "RobotCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitPointsChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPowerChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FZeroHitPointsDelegate);

UCLASS()
class SCRAPYARD_API ARobotCharacter : public ACharacter, public ITargetableInterface
{
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  ARobotCharacter(const class FObjectInitializer& ObjectInitializer);

  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  virtual void Landed(const FHitResult & Hit) override;

  void SetupRobotHUDWidget();

  UPROPERTY()
  UPartAssignment* PartAssignment;

  UPROPERTY(EditAnywhere)
  URobotBodyComponent* RobotBodyComponent;

  UPROPERTY(EditAnywhere)
  URobotTargetingComponent* RobotTargetingComponent;

  UPROPERTY(EditAnywhere)
  UTargetableComponent* TargetableComponent;

  UPROPERTY(Replicated)
  bool bTargetAcquired;

// stats
  UPROPERTY()
  URobotStats* RobotStats;

//  UPROPERTY(Replicated)
  UPROPERTY(ReplicatedUsing=OnRep_HitPoints)
  int32 HitPoints = 0;
  UPROPERTY(ReplicatedUsing=OnRep_Power)
  int32 Power = 0;

  UFUNCTION()
  virtual void OnRep_HitPoints();

  UFUNCTION()
  virtual void OnRep_Power();

// camera
  UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
  class UCameraComponent* OurCamera;
  UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
  class USpringArmComponent* CameraBoom;

  void SetupCamera();

// movement
  UFUNCTION()
  virtual void Axis_MoveX(float AxisValue);
  UFUNCTION()
  virtual void Axis_MoveY(float AxisValue);
  UFUNCTION()
  virtual void Axis_TurnZ(float AxisValue);
  UFUNCTION()
  virtual void Axis_TurnY(float AxisValue);

  virtual void StartBoosting();
  virtual void StopBoosting();

  UPROPERTY()//Replicated
  uint8 FireMode;

  virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

  UFUNCTION(NetMulticast, Unreliable)
  void MulticastShowDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser, FHitResult HitInfo);

// abilities 
  UPROPERTY(Replicated)
  AScrapyardAbility* HeadAbility;
  UPROPERTY(Replicated)
  AScrapyardAbility* CoreAbility;
  UPROPERTY(Replicated)
  AScrapyardAbility* ArmsAbility;
  UPROPERTY(Replicated)
  AScrapyardAbility* LegsAbility;
  UPROPERTY(Replicated)
  AScrapyardAbility* LeftHandheldAbility;
  UPROPERTY(Replicated)
  AScrapyardAbility* RightHandheldAbility;

// TODO: get rid of this
  UPROPERTY(Replicated)
  AScrapyardAbility* WeaponAbility;

  UFUNCTION()
  virtual void StartFire(uint8 FireModeNum);
  UFUNCTION()
  virtual void StopFire(uint8 FireModeNum);
  UFUNCTION()
  virtual void StopFiring();

  // redirect engine version
  virtual void PawnStartFire(uint8 FireModeNum = 0) override
  {
    StartFire(FireModeNum);
  }

  inline void SetPendingFire(uint8 InFireMode, bool bNowFiring)
  {
    UE_LOG(LogTemp, Warning, TEXT("ARobotCharacter::SetPendingFire"));
// extend the PendingFire Array if it's not big enough
    if (PendingFire.Num() < InFireMode + 1 )
    {
      PendingFire.SetNumZeroed(InFireMode + 1);
    }
    PendingFire[InFireMode] = bNowFiring ? 1 : 0;
  }

  inline void ClearPendingFire()
  {
    for (int32 i = 0; i < PendingFire.Num(); i++)
    {
      PendingFire[i] = 0;
    }
  }

  inline bool IsPendingFire(uint8 InFireMode) const
  {
    return (InFireMode < PendingFire.Num() && PendingFire[InFireMode] != 0);
  }

  UFUNCTION(NetMulticast, Reliable)
  void MulticastSetPartAssignmentFromIDs(FPartAssignmentIDs NewPartAssignmentIDs);

  FHitPointsChangedDelegate HitPointsChangedDelegate;
  FPowerChangedDelegate PowerChangedDelegate;
  FZeroHitPointsDelegate ZeroHitPointsDelegate;
  
  UPROPERTY(EditAnywhere)
  int32 Team;

// Targetable Interfacte
  UFUNCTION()
  virtual bool IsTargetableBy(ARobotCharacter* Robot) override;
//  virtual bool IsTargetableBy_Implementation(ARobotCharacter* Robot) override;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  virtual void PostInitializeComponents() override;

  UPROPERTY()
  TArray<uint8> PendingFire;

  void SetupBody();
  void SetupStats();
  void SetupAbilities();

  UFUNCTION()
  void OnStatsUpdated();

  friend class URobotTunerWidget;

};
