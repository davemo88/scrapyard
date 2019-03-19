// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotTargetingComponent.h"
#include "Player/RobotPlayerController.h"
#include "Engine.h"


// Sets default values for this component's properties
URobotTargetingComponent::URobotTargetingComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  // ...
  TargetingBoxComponent = CreateDefaultSubobject<UTargetingBoxComponent>(TEXT("TargetingBoxComponent"));
  TargetingBoxComponent->SetupAttachment(this);
  TargetingBoxComponent->SetBoxExtent(FVector(1000.0f,100.0f,100.0f));
  TargetingBoxComponent->SetRelativeLocation(FVector(1000.0f,0.0f,0.0f));
  TargetingBoxComponent->SetHiddenInGame(false);
}


// Called when the game starts
void URobotTargetingComponent::BeginPlay()
{
  Super::BeginPlay();

  // ...
  
}


// Called every frame
void URobotTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

//TODO: add flag for relative / world location
TArray<FVector> URobotTargetingComponent::GetBoxFaceVertices()
{
  TArray<FVector> Vertices;

  FVector Extent = TargetingBoxComponent->GetScaledBoxExtent();
//  FVector Extent = RelativeRotation.RotateVector(TargetingBoxComponent->GetScaledBoxExtent());
//  FVector Extent = TargetingBoxComponent->GetUnscaledBoxExtent();
//  UE_LOG(LogTemp, Warning, TEXT("Box Extent: %s"), *Extent.ToString());

  Vertices.Add(FVector(Extent.X, Extent.Y * -0.5f, Extent.Z));
  Vertices.Add(FVector(Extent.X, Extent.Y * 0.5f, Extent.Z));
  Vertices.Add(FVector(Extent.X, Extent.Y * 0.5f, 0.0f));
  Vertices.Add(FVector(Extent.X, Extent.Y * -0.5f, 0.0f));

//  Vertices.Add(FVector(Extent.X, -Extent.Y, Extent.Z));
//  Vertices.Add(FVector(Extent.X, Extent.Y, Extent.Z));
//  Vertices.Add(FVector(Extent.X, Extent.Y, 0.0f));
//  Vertices.Add(FVector(Extent.X, -Extent.Y, 0.0f));

  return Vertices;
}

//TODO: add flag for relative / world location
FVector URobotTargetingComponent::GetBoxFaceCenter()
{
  FVector Extent = TargetingBoxComponent->GetScaledBoxExtent();

//  UE_LOG(LogTemp, Warning, TEXT("%s"), *Extent.ToString());
//
  FVector FaceCenter = FVector(Extent.X, 0.0f, Extent.Z * 0.5f);

  return FaceCenter;

//  return RelativeRotation.RotateVector(FVector(Extent.X * 0.5f, Extent.Y, Extent.Z * 0.5));
}
