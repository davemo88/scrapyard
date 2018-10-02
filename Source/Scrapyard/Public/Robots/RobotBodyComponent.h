// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "RobotBodyComponent.generated.h"

class URobotPartComponent;
class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class UHandheldPart;
struct FRobotPartAssignment;

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
// default skeletal mesh
  FString DefaultMeshPath = "/Game/Mannequin/Mesh/SK_Mannequin";

// animation instance class
// https://answers.unrealengine.com/questions/153496/how-to-set-animation-blueprint-in-c.html
  FString DefaultAnimPath = "AnimBlueprintGeneratedClass'/Game/Mannequin/Animations/MannequinAnimBlueprint.MannequinAnimBlueprint_C'";

// part components
  UPROPERTY(BlueprintReadOnly)
  URobotPartComponent* HeadComponent;
  UPROPERTY(BlueprintReadOnly)
  URobotPartComponent* CoreComponent;
  UPROPERTY(BlueprintReadOnly)
  URobotPartComponent* ArmsComponent;
  UPROPERTY(BlueprintReadOnly)
  URobotPartComponent* LegsComponent;
  UPROPERTY(BlueprintReadOnly)
  URobotPartComponent* RightHandheldComponent;

//  UPROPERTY(EditAnywhere, BlueprintReadWrite)
//  UParticleSystemComponent* BoostingParticleComponent;

//  void SetPart(URobotPartComponent* Component, URobotPart* NewPart);
//
//  void SetHead(UHeadPart* NewHead);
//  void SetCore(UCorePart* NewCore);
//  void SetArms(UArmsPart* NewArms);
//  void SetLegs(ULegsPart* NewLegs);
//  void SetRightHandheld(UHandheldPart* NewRightHandheld);

};
