// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Robots/RobotBodyComponent.h"
#include "Robots/RobotPartAssignment.h"
#include "Robots/RobotStats.h"
#include "Ability/ScrapyardAbility.h"
#include "RobotCharacter.generated.h"

UCLASS()
class SCRAPYARD_API ARobotCharacter : public ACharacter
{
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  ARobotCharacter(const class FObjectInitializer& ObjectInitializer);

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UPROPERTY()
  TArray<uint8> PendingFire;

public:  
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// part assignment
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  URobotPartAssignment* RobotPartAssignment;
// body
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  URobotBodyComponent* RobotBodyComponent;
// stats
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  URobotStats* RobotStats;

  void SetupBody();
  void SetupPartAssignment();
  void SetupStats();
  void SetupAbilities();

  UFUNCTION(BlueprintCallable)
  void UpdateStats();

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 Durability;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 Power = 0;

// camera
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  class UCameraComponent* OurCamera;
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  class USpringArmComponent* CameraBoom;

  void SetupCamera();

// movement
  UFUNCTION()
  virtual void Axis_MoveX(float AxisValue);
  UFUNCTION()
  virtual void Axis_MoveY(float AxisValue);
  UFUNCTION()
  virtual void Axis_Boost(float AxisValue);

  UPROPERTY()//Replicated
  uint8 FireMode;

//  virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override

// abilities 
  UScrapyardAbility* WeaponAbility;

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
  
};
