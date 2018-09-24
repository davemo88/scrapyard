// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/HandheldPart.h"
#include "RobotBodyComponent.generated.h"


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
  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// default skeletal mesh
  FString DefaultMeshPath = "/Game/Mannequin/Mesh/SK_Mannequin";

// animation instance class
// https://answers.unrealengine.com/questions/153496/how-to-set-animation-blueprint-in-c.html
  FString DefaultAnimPath = "AnimBlueprintGeneratedClass'/Game/Mannequin/Animations/MannequinAnimBlueprint.MannequinAnimBlueprint_C'";

// part components
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UHeadPart* Head;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UCorePart* Core;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UArmsPart* Arms;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  ULegsPart* Legs;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UHandheldPart* RightHandheld;

//  UPROPERTY(EditAnywhere, BlueprintReadWrite)
//  UParticleSystemComponent* BoostingParticleComponent;

  void SetHead(UHeadPart* NewHead);
  void SetCore(UCorePart* NewCore);
  void SetArms(UArmsPart* NewArms);
  void SetLegs(ULegsPart* NewLegs);
  void SetRightHandheld(UHandheldPart* NewRightHandheld);
};
