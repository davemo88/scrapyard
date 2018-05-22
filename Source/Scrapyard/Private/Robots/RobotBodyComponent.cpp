// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotBodyComponent.h"
#include "Components/SceneComponent.h"
#include "Robots/RobotPartAssignment.h"
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

	RobotPartAssignment = CreateDefaultSubobject<URobotPartAssignment>(TEXT("RobotPartAssignment"));

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
//	RightHandheldComponent->SetMasterPoseComponent(this);
	
//	BoostingParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BoostingParticleComponent"));
//	BoostingParticleComponent->SetupAttachment(this);


}

void URobotBodyComponent::SetPartAssignment(URobotPartAssignment* PartAssignment)
{
	RobotPartAssignment = PartAssignment;
	HeadComponent->AssignPart(PartAssignment->Head);
	CoreComponent->AssignPart(PartAssignment->Core);
	ArmsComponent->AssignPart(PartAssignment->Arms);
	LegsComponent->AssignPart(PartAssignment->Legs);
}

void URobotBodyComponent::SetHead(UHeadPart* NewHead)
{
	RobotPartAssignment->Head = NewHead;
	HeadComponent->AssignPart(NewHead);
}

void URobotBodyComponent::SetCore(UCorePart* NewCore)
{
	RobotPartAssignment->Core = NewCore;
	CoreComponent->AssignPart(NewCore);
}

void URobotBodyComponent::SetArms(UArmsPart* NewArms)
{
	RobotPartAssignment->Arms = NewArms;
	ArmsComponent->AssignPart(NewArms);
}
 
void URobotBodyComponent::SetLegs(ULegsPart* NewLegs)
{
	RobotPartAssignment->Legs = NewLegs;
	LegsComponent->AssignPart(NewLegs);
}
// Called when the game starts
void URobotBodyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URobotBodyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}