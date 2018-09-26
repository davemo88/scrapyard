// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotBodyComponent.h"
#include "Components/SceneComponent.h"
#include "ConstructorHelpers.h"
#include "Animation/AnimBlueprintGeneratedClass.h"


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

  Head = CreateDefaultSubobject<UHeadPart>(TEXT("HeadComponent"));
  Core = CreateDefaultSubobject<UCorePart>(TEXT("CoreComponent"));
  Arms = CreateDefaultSubobject<UArmsPart>(TEXT("ArmsComponent"));
  Legs = CreateDefaultSubobject<ULegsPart>(TEXT("LegsComponent"));
  RightHandheld = CreateDefaultSubobject<UHandheldPart>(TEXT("RightHandheldComponent"));

  Head->SetupAttachment(this);
  Core->SetupAttachment(this);
  Arms->SetupAttachment(this);
  Legs->SetupAttachment(this);
  RightHandheld->SetupAttachment(this);

  Head->SetMasterPoseComponent(this);
  Core->SetMasterPoseComponent(this);
  Arms->SetMasterPoseComponent(this);
  Legs->SetMasterPoseComponent(this);
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

void URobotBodyComponent::SetHead(UHeadPart* NewHead)
{
  Head = NewHead;
}

void URobotBodyComponent::SetCore(UCorePart* NewCore)
{
  Core = NewCore;
}

void URobotBodyComponent::SetArms(UArmsPart* NewArms)
{
  Arms = NewArms;
}
 
void URobotBodyComponent::SetLegs(ULegsPart* NewLegs)
{
  Legs = NewLegs;
}

void URobotBodyComponent::SetRightHandheld(UHandheldPart* NewRightHandheld)
{
  RightHandheld = NewRightHandheld;
}

void URobotBodyComponent::SetPart(URobotPart* Component, TSubclassOf<URobotPart> NewPartClass)
{
  Component = NewObject<URobotPart>(this, *NewPartClass);
  Component->SetupAttachment(this);
  Component->RegisterComponent();
}

void URobotBodyComponent::SetHead(TSubclassOf<UHeadPart> NewHeadClass)
{
  SetPart(Head, NewHeadClass);
}

void URobotBodyComponent::SetCore(TSubclassOf<UCorePart> NewCoreClass)
{
  SetPart(Core, NewCoreClass);
}

void URobotBodyComponent::SetArms(TSubclassOf<UArmsPart> NewArmsClass)
{
  SetPart(Arms, NewArmsClass);
}
 
void URobotBodyComponent::SetLegs(TSubclassOf<ULegsPart> NewLegsClass)
{
  SetPart(Legs, NewLegsClass);
}

void URobotBodyComponent::SetRightHandheld(TSubclassOf<UHandheldPart> NewRightHandheldClass)
{
  SetPart(RightHandheld, NewRightHandheldClass);
}

// Called every frame
void URobotBodyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // ...
}
