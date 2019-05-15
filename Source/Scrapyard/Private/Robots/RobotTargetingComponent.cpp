// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotTargetingComponent.h"
#include "Player/RobotPlayerController.h"
#include "Player/RobotPlayerState.h"
#include "Targeting/RectangularTargetingProfile.h"
#include "Targeting/ConeTargetingProfile.h"
#include "Robots/RobotCharacter.h"
#include "Engine.h"
#include "UnrealNetwork.h"


// Sets default values for this component's properties
URobotTargetingComponent::URobotTargetingComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  bTargetAcquired = false;

  TargetingProfile = CreateDefaultSubobject<URectangularTargetingProfile>(TEXT("TargetingProfile"));
//  TargetingProfile = CreateDefaultSubobject<UConeTargetingProfile>(TEXT("TargetingProfile"));

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
//  UE_LOG(LogTemp, Warning, TEXT("%s::IsTargetAcquired"), *GetName());
  if (GetOwner()->HasAuthority())
  {
    bTargetAcquired = false;
    for (AActor* Actor: Targetables)
    {
//      UE_LOG(LogTemp, Warning, TEXT("%s targeting %s"), *GetName(), *Actor->GetName());
      bTargetAcquired = bTargetAcquired || IsTargeted(Actor);
//      FString TargetAcquired = bTargetAcquired ? "True" : "False";
//      UE_LOG(LogTemp, Warning, TEXT("bTargetAcquired = %s"), *TargetAcquired);
    }
  }
}

bool URobotTargetingComponent::IsTargetAcquired()
{
  return bTargetAcquired;
}

bool URobotTargetingComponent::IsTargeted(AActor* Actor) const
{
  if (TargetingProfile != nullptr)
  {
    FVector OtherRelativeLocation = GetLocationRelativeToView(Actor);
    return TargetingProfile->IsTargeted(OtherRelativeLocation);
  }

  return false;
}

TArray<FVector> URobotTargetingComponent::GetFaceVerts() const
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::GetFaceVerts"), *GetName());
  static TArray<FVector> FaceVerts = TargetingProfile->InitFaceVerts();

  return FaceVerts;
}

void URobotTargetingComponent::AddTargetable(AActor* Actor)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::AddTargetable"), *GetName());
  UE_LOG(LogTemp, Warning, TEXT("%s::AddTargetable - %s"), *GetName(), *Actor->GetName());
  Targetables.AddUnique(Actor);
}

void URobotTargetingComponent::RemoveTargetable(AActor* Actor)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::RemoveTargetable"), *GetName());
  Targetables.Remove(Actor);
}

bool URobotTargetingComponent::IsTargetable(AActor* Actor) const
{
  ARobotCharacter* OwnerChar = Cast<ARobotCharacter>(GetOwner());
  if (ARobotCharacter* OtherChar = Cast<ARobotCharacter>(Actor))
  {
    if (OwnerChar->Team != OtherChar->Team)
    {
      return true; 
    }
  }

  return false;
}

//float URobotTargetingComponent::GetRange()
//{
//  return TargetingProfile->GetRange();
//}

FVector URobotTargetingComponent::GetLocationRelativeToView(AActor* OtherActor) const
{
  ARobotCharacter* OwnerChar = Cast<ARobotCharacter>(GetOwner());
  FVector OwnerLocation = OwnerChar->GetActorLocation();
  FRotator ViewRotation = OwnerChar->GetViewRotation();
  FVector TargetingOffset = TargetingProfile->TargetingOffset;
  FVector RotatedTargetingOffset = ViewRotation.RotateVector(TargetingOffset);
  FRotator InverseViewRotation = ViewRotation.GetInverse();
  FVector TargetingOrigin = OwnerLocation + RotatedTargetingOffset;
  FVector OtherRelativeLocation = InverseViewRotation.RotateVector(OtherActor->GetActorLocation()-TargetingOrigin);

  return OtherRelativeLocation;
}
