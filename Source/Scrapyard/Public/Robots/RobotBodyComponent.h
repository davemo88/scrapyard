// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "RobotBodyComponent.generated.h"

class URobotPartComponent;
class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class UHandheldPart;
class UPartAssignment;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCRAPYARD_API URobotBodyComponent : public USkeletalMeshComponent
{
  GENERATED_BODY()
  // Sets default values for this component's properties
  URobotBodyComponent();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

public:  

  void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);

//  void SetMasterPoseComponent(USkeletalMeshComponent* MasterPoseComponent);

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UPartAssignment* PartAssignment;

// part components
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  URobotPartComponent* HeadComponent;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  URobotPartComponent* CoreComponent;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  URobotPartComponent* ArmsComponent;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  URobotPartComponent* LegsComponent;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  URobotPartComponent* LeftHandheldComponent;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  URobotPartComponent* RightHandheldComponent;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  URobotPartComponent* FirstChipComponent;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  URobotPartComponent* SecondChipComponent;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  URobotPartComponent* ThirdChipComponent;

// other visual effects
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UParticleSystemComponent* BoostingParticleComponent;

};
