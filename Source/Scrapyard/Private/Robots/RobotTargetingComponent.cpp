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
  TargetingBoxComponent->SetBoxExtent(FVector(100.0f,1000.0f,100.0f));
  TargetingBoxComponent->SetRelativeLocation(FVector(0.0f,1000.0f,100.0f));
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

  // ...
  ARobotCharacter* RobotOwner = Cast<ARobotCharacter>(GetOwner());
  
  if (ARobotPlayerController* PC = Cast<ARobotPlayerController>(RobotOwner->GetController()))
  {
    float MouseX;
    float MouseY;
    PC->GetMousePosition(MouseX, MouseY);
    MouseX = FMath::Clamp(MouseX, 0.0f, float(GSystemResolution.ResX));
    MouseY = FMath::Clamp(MouseY, 0.0f, float(GSystemResolution.ResY));

    uint32 CenterX = GSystemResolution.ResX / 2;
    uint32 CenterY = GSystemResolution.ResY / 2;

    float TurnRateZ = float(MouseX - CenterX) / float(CenterX);
    float TurnRateY = float(MouseY - CenterY) / float(CenterY);

    float MaxTargetingAngleZ = 45.0f;
    float MaxTargetingAngleY = 35.0f;
//    float MaxTargetingAngleY = 45.0f;

    FRotator TargetingRotation = FRotator(0.0f, TurnRateZ * MaxTargetingAngleZ, TurnRateY * MaxTargetingAngleY);

    SetRelativeRotation(TargetingRotation);
  }
}

TArray<FVector> URobotTargetingComponent::GetBoxFaceVertices()
{
  TArray<FVector> Vertices;

  FVector Extent = TargetingBoxComponent->GetScaledBoxExtent();

  Vertices.Add(RelativeRotation.RotateVector(FVector(Extent.X * 0.5f, Extent.Y, Extent.Z * 0.5)));
  Vertices.Add(RelativeRotation.RotateVector(FVector(Extent.X * -0.5f, Extent.Y, Extent.Z * 0.5)));
  Vertices.Add(RelativeRotation.RotateVector(FVector(Extent.X * 0.5f, Extent.Y, Extent.Z * -0.5)));
  Vertices.Add(RelativeRotation.RotateVector(FVector(Extent.X * -0.5f, Extent.Y, Extent.Z * -0.5)));

  return Vertices;
}

FVector URobotTargetingComponent::GetBoxFaceCenter()
{
  FVector Extent = TargetingBoxComponent->GetScaledBoxExtent();

//  UE_LOG(LogTemp, Warning, TEXT("%s"), *Extent.ToString());

  return RelativeRotation.RotateVector(FVector(Extent.X * 0.5f, Extent.Y, Extent.Z * 0.5));
}
