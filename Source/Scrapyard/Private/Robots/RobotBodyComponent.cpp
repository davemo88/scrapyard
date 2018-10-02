// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotBodyComponent.h"
#include "Components/SceneComponent.h"
#include "ConstructorHelpers.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Robots/RobotPartComponent.h"


// Sets default values for this component's properties
URobotBodyComponent::URobotBodyComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  bVisible = false;
  
  static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(*DefaultMeshPath);
  SetSkeletalMesh(DefaultMesh.Object);
  static ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass> DefaultAnimBP(*DefaultAnimPath);
  SetAnimInstanceClass(DefaultAnimBP.Object);

  FVector DefaultLoc = FVector(0.f, 0.f, -85.f);
  FRotator DefaultRot = FRotator(0.f, -90.f, 0.f);
  SetRelativeLocation(DefaultLoc);
  SetRelativeRotation(DefaultRot);

  HeadComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("HeadComponent"));
  CoreComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("CoreComponent"));
  ArmsComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("ArmsComponent"));
  LegsComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("LegsComponent"));
  RightHandheldComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("RightHandheldComponent"));

  HeadComponent->SetupAttachment(this);
  CoreComponent->SetupAttachment(this);
  ArmsComponent->SetupAttachment(this);
  LegsComponent->SetupAttachment(this);
  RightHandheldComponent->SetupAttachment(this);

  HeadComponent->SetMasterPoseComponent(this);
  CoreComponent->SetMasterPoseComponent(this);
  ArmsComponent->SetMasterPoseComponent(this);
  LegsComponent->SetMasterPoseComponent(this);
//  RightHandheldComponent->SetMasterPoseComponent(this);
  
//  BoostingParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BoostingParticleComponent"));
//  BoostingParticleComponent->SetupAttachment(this);


}

// Called when the game starts
void URobotBodyComponent::BeginPlay()
{
  Super::BeginPlay();

  // ...
  
}

//void URobotBodyComponent::SetPart(URobotPartComponent* Component, URobotPart* NewPart)
//{      
//  Component->SetRobotPart(NewPart);
//}
//
//void URobotBodyComponent::SetHead(UHeadPart* NewHead)
//{
//   
//}
//
//void URobotBodyComponent::SetCore(UCorePart* NewCore)
//{
//  PartAssignment.Core = NewCore;
//}
//
//void URobotBodyComponent::SetArms(UArmsPart* NewArms)
//{
//  PartAssignment.Arms = NewArms;
//}
// 
//void URobotBodyComponent::SetLegs(ULegsPart* NewLegs)
//{
//  PartAssignment.Legs = NewLegs;
//}
//
//void URobotBodyComponent::SetRightHandheld(UHandheldPart* NewRightHandheld)
//{
//  PartAssignment.RightHandheld = NewRightHandheld;
//}
