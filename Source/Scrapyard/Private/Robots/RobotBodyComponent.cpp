// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotBodyComponent.h"
#include "Components/SceneComponent.h"
#include "ConstructorHelpers.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Robots/RobotPartComponent.h"
#include "Parts/RobotPartAssignment.h"
#include "Parts/RobotPart.h"
#include "Parts/RobotPartAssets.h"
#include "Abilities/HitscanAbility.h"


// Sets default values for this component's properties
URobotBodyComponent::URobotBodyComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

//  bVisible = false;

//  if (URobotPart::RobotPartAssetsBP != nullptr)
//  {
//    SetSkeletalMesh(URobotPart::RobotPartAssetsBP->GetAsset<USkeletalMesh>(URobotPart::RobotPartAssetsBP->RobotSkeletalMesh));
//    SetAnimInstanceClass(URobotPart::RobotPartAssetsBP->RobotAnimInstance);
//  }

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

  PartAssignment = CreateDefaultSubobject<URobotPartAssignment>(TEXT("PartAssignment"));
  
  PartAssignment->HeadAssignmentChangedDelegate.AddDynamic(HeadComponent, &URobotPartComponent::SetRobotPart);
  PartAssignment->CoreAssignmentChangedDelegate.AddDynamic(CoreComponent, &URobotPartComponent::SetRobotPart);
  PartAssignment->ArmsAssignmentChangedDelegate.AddDynamic(ArmsComponent, &URobotPartComponent::SetRobotPart);
  PartAssignment->LegsAssignmentChangedDelegate.AddDynamic(LegsComponent, &URobotPartComponent::SetRobotPart);

  WeaponAbilityComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponAbilityComponent"));
  WeaponAbilityComponent->SetupAttachment(this);
  WeaponAbilityComponent->SetChildActorClass(AHitscanAbility::StaticClass());

//  BoostingParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BoostingParticleComponent"));
//  BoostingParticleComponent->SetupAttachment(this);

}

// Called when the game starts
void URobotBodyComponent::BeginPlay()
{
  Super::BeginPlay();

  // ...
  
}

void URobotBodyComponent::SetMasterPoseComponent(USkeletalMeshComponent* MasterPoseComponent)
{
  HeadComponent->SetMasterPoseComponent(MasterPoseComponent);
  CoreComponent->SetMasterPoseComponent(MasterPoseComponent);
  ArmsComponent->SetMasterPoseComponent(MasterPoseComponent);
  LegsComponent->SetMasterPoseComponent(MasterPoseComponent);
//  RightHandheldComponent->SetMasterPoseComponent(MasterPoseComponent);
}

