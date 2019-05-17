// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotBodyComponent.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Robots/RobotPartComponent.h"
#include "Parts/PartAssignment.h"
#include "Parts/RobotPart.h"
#include "Parts/PartAssets.h"
#include "Robots/RobotCharacter.h"
#include "Abilities/HitscanAbility.h"
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

  if (UScrapyardGameInstance::AssetsBP != nullptr)
  {
//    SetSkeletalMesh(UScrapyardGameInstance::AssetsBP->PartAssetsBP->GetAsset<USkeletalMesh>(URobotPart::PartAssetsBP->RobotSkeletalMesh));
    SetSkeletalMesh(UScrapyardGameInstance::AssetsBP->PartAssetsBP->RobotSkeletalMesh);
    SetAnimInstanceClass(UScrapyardGameInstance::AssetsBP->PartAssetsBP->RobotAnimInstance);
  }

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

  PartAssignment = CreateDefaultSubobject<UPartAssignment>(TEXT("PartAssignment"));
  
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

void URobotBodyComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
