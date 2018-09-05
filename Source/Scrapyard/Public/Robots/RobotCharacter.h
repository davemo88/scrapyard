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

// firing weapons
//  AScrapyardWeapon* CurrentWeapon

  UFUNCTION()
  virtual void StartFire(uint8 FireModeNum);
  UFUNCTION()
  virtual void StopFire(uint8 FireModeNum);
  UFUNCTION()
  virtual void StopFiring();
  
};
