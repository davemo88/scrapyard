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
    SetSkeletalMesh(UScrapyardGameInstance::AssetsBP->PartAssetsBP->RobotSkeletalMesh);
    SetAnimInstanceClass(UScrapyardGameInstance::AssetsBP->PartAssetsBP->RobotAnimInstance);
  }

  HeadComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("HeadComponent"));
  CoreComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("CoreComponent"));
  ArmsComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("ArmsComponent"));
  LegsComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("LegsComponent"));
  LeftHandheldComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("LeftHandheldComponent"));
  RightHandheldComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("RightHandheldComponent"));
  FirstChipComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("FirstChipComponent"));
  SecondChipComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("SecondChipComponent"));
  ThirdChipComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("ThirdChipComponent"));

  HeadComponent->SetupAttachment(this);
  CoreComponent->SetupAttachment(this);
  ArmsComponent->SetupAttachment(this);
  LegsComponent->SetupAttachment(this);

  HeadComponent->SetMasterPoseComponent(this);
  CoreComponent->SetMasterPoseComponent(this);
  ArmsComponent->SetMasterPoseComponent(this);
  LegsComponent->SetMasterPoseComponent(this);

// TODO: do these need the master pose? or are they socketed to the other parts?
  LeftHandheldComponent->SetupAttachment(this);
  RightHandheldComponent->SetupAttachment(this);
  FirstChipComponent->SetupAttachment(this);
  SecondChipComponent->SetupAttachment(this);
  ThirdChipComponent->SetupAttachment(this);

  if (ARobotCharacter* OwningRobot = Cast<ARobotCharacter>(GetOwner()))
  {
//    PartAssignment = CreateDefaultSubobject<UPartAssignment>(TEXT("PartAssignment"));

    PartAssignment = OwningRobot->PartAssignment;

    if (PartAssignment != nullptr)
    {
      
      PartAssignment->HeadAssignmentChangedDelegate.AddDynamic(HeadComponent, &URobotPartComponent::SetRobotPart);
      PartAssignment->CoreAssignmentChangedDelegate.AddDynamic(CoreComponent, &URobotPartComponent::SetRobotPart);
      PartAssignment->ArmsAssignmentChangedDelegate.AddDynamic(ArmsComponent, &URobotPartComponent::SetRobotPart);
      PartAssignment->LegsAssignmentChangedDelegate.AddDynamic(LegsComponent, &URobotPartComponent::SetRobotPart);
    
      PartAssignment->LeftHandheldAssignmentChangedDelegate.AddDynamic(LeftHandheldComponent, &URobotPartComponent::SetRobotPart);
      PartAssignment->RightHandheldAssignmentChangedDelegate.AddDynamic(RightHandheldComponent, &URobotPartComponent::SetRobotPart);
      PartAssignment->FirstChipAssignmentChangedDelegate.AddDynamic(FirstChipComponent, &URobotPartComponent::SetRobotPart);
      PartAssignment->SecondChipAssignmentChangedDelegate.AddDynamic(SecondChipComponent, &URobotPartComponent::SetRobotPart);
      PartAssignment->ThirdChipAssignmentChangedDelegate.AddDynamic(ThirdChipComponent, &URobotPartComponent::SetRobotPart);
    
    }

  }

  WeaponAbilityComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponAbilityComponent"));
  WeaponAbilityComponent->SetupAttachment(this);
//TODO: get from handheld part 
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
