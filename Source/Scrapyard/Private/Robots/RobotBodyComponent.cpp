// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotBodyComponent.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Robots/RobotPartComponent.h"
#include "Parts/PartAssignment.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/BoosterPart.h"
#include "Parts/HandheldPart.h"
#include "Parts/PartAssets.h"
#include "Robots/RobotCharacter.h"
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
  BoosterComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("BoosterComponent"));
  LeftHandheldComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("LeftHandheldComponent"));
  RightHandheldComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("RightHandheldComponent"));
  FirstChipComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("FirstChipComponent"));
  SecondChipComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("SecondChipComponent"));
  ThirdChipComponent = CreateDefaultSubobject<URobotPartComponent>(TEXT("ThirdChipComponent"));

  HeadComponent->SetupAttachment(this);
  CoreComponent->SetupAttachment(this);
  ArmsComponent->SetupAttachment(this);
  LegsComponent->SetupAttachment(this);
  BoosterComponent->SetupAttachment(this);

  HeadComponent->SetMasterPoseComponent(this);
  CoreComponent->SetMasterPoseComponent(this);
  ArmsComponent->SetMasterPoseComponent(this);
  LegsComponent->SetMasterPoseComponent(this);
  BoosterComponent->SetMasterPoseComponent(this);

// TODO: do these need the master pose? or are they socketed to the other parts?
// i think socketed
  LeftHandheldComponent->SetupAttachment(this);
  LeftHandheldComponent->SetRelativeLocation(FVector(70,120,70));

  RightHandheldComponent->SetupAttachment(this);
  RightHandheldComponent->SetRelativeLocation(FVector(-70,120,70));

  FirstChipComponent->SetupAttachment(this);
  SecondChipComponent->SetupAttachment(this);
  ThirdChipComponent->SetupAttachment(this);

//  FName RightHandheldSocket = TEXT("RightHandheldSocket");
//  RightHandheldComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), RightHandheldSocket);

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

void URobotBodyComponent::SetPartAssignment(UPartAssignment* NewPartAssignment)
{
  PartAssignment = NewPartAssignment;

  if (PartAssignment->GetHead())
  {
    HeadComponent->SetRobotPart(PartAssignment->GetHead());    
  }
  if (PartAssignment->GetCore())
  {
    CoreComponent->SetRobotPart(PartAssignment->GetCore());    
  }
  if (PartAssignment->GetArms())
  {
    ArmsComponent->SetRobotPart(PartAssignment->GetArms());    
  }
  if (PartAssignment->GetLegs())
  {
    LegsComponent->SetRobotPart(PartAssignment->GetLegs());    
  }
  if (PartAssignment->GetBooster())
  {
    BoosterComponent->SetRobotPart(PartAssignment->GetBooster());    
  }
  if (PartAssignment->GetRightHandheld())
  {
    RightHandheldComponent->SetRobotPart(PartAssignment->GetRightHandheld());    
  }

  PartAssignment->HeadAssignedDelegate.AddDynamic(HeadComponent, &URobotPartComponent::SetRobotPart);
  PartAssignment->CoreAssignedDelegate.AddDynamic(CoreComponent, &URobotPartComponent::SetRobotPart);
  PartAssignment->ArmsAssignedDelegate.AddDynamic(ArmsComponent, &URobotPartComponent::SetRobotPart);
  PartAssignment->LegsAssignedDelegate.AddDynamic(LegsComponent, &URobotPartComponent::SetRobotPart);
  PartAssignment->BoosterAssignedDelegate.AddDynamic(BoosterComponent, &URobotPartComponent::SetRobotPart);

  PartAssignment->LeftHandheldAssignedDelegate.AddDynamic(LeftHandheldComponent, &URobotPartComponent::SetRobotPart);
  PartAssignment->RightHandheldAssignedDelegate.AddDynamic(RightHandheldComponent, &URobotPartComponent::SetRobotPart);
  PartAssignment->FirstChipAssignedDelegate.AddDynamic(FirstChipComponent, &URobotPartComponent::SetRobotPart);
  PartAssignment->SecondChipAssignedDelegate.AddDynamic(SecondChipComponent, &URobotPartComponent::SetRobotPart);
  PartAssignment->ThirdChipAssignedDelegate.AddDynamic(ThirdChipComponent, &URobotPartComponent::SetRobotPart);
}
