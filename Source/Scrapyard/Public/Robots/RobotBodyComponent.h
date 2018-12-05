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
class URobotPartAssignment;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCRAPYARD_API URobotBodyComponent : public USkeletalMeshComponent
{
  GENERATED_BODY()
  // Sets default values for this component's properties
  URobotBodyComponent();

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

// TODO: put these asset refs into a blueprint
// default skeletal mesh
  FString DefaultMeshPath = "/Game/Mannequin/Mesh/SK_Mannequin";
// https://answers.unrealengine.com/questions/153496/how-to-set-animation-blueprint-in-c.html
  FString DefaultAnimPath = "AnimBlueprintGeneratedClass'/Game/Mannequin/Animations/MannequinAnimBlueprint.MannequinAnimBlueprint_C'";

public:  

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  URobotPartAssignment* PartAssignment;

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
  URobotPartComponent* RightHandheldComponent;
//  UPROPERTY(EditAnywhere, BlueprintReadWrite)
//  UParticleSystemComponent* BoostingParticleComponent;
//

  UPROPERTY()
  UChildActorComponent* WeaponAbilityComponent;


};
