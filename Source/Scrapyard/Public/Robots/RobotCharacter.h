// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Scrapyard.h"
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

UENUM()
enum class EControlType : uint8
{
  CONTROL_Normal        UMETA(DisplayName="Normal"),
  CONTROL_Rectangle     UMETA(DisplayName="Rectangle"),
  CONTROL_Ellipse       UMETA(DisplayName="Ellipse")//,
//  CONTROL_Lerp          UMETA(DisplayName="Lerp")
};

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

  void SetPartAssignment(UPartAssignment* NewPartAssignment);

  UPROPERTY()
  UPartAssignment* PartAssignment;

  UPROPERTY(EditAnywhere)
  URobotBodyComponent* RobotBodyComponent;

  UPROPERTY(EditAnywhere)
  URobotTargetingComponent* RobotTargetingComponent;

  UPROPERTY(EditAnywhere)
  UTargetableComponent* TargetableComponent;

  bool IsTargetAcquired();

// stats
  UPROPERTY()
  URobotStats* RobotStats;

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
    UE_LOG(LogCharacter, Verbose, TEXT("ARobotCharacter::SetPendingFire"));
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

// for experimental movement controls
  UPROPERTY(EditAnywhere)
  EControlType ControlType;

  UPROPERTY(EditAnywhere)
  uint32 DeadZoneFactor = 10;
  FVector2D GetDeadZoneHalfWidth();

  FVector2D GetControlEllipseIntersection(FVector2D Mouse);

  bool IsInControlEllipse(FVector2D Mouse);

  bool IsInXDeadZone(FVector2D Mouse);
  bool IsInYDeadZone(FVector2D Mouse);

  UPROPERTY(EditAnywhere)
  float MaxPitchRate = 1.0f;

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
