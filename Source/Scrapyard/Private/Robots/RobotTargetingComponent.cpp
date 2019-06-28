// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotTargetingComponent.h"
#include "Game/RobotGameState.h"
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

  SetNetAddressable();
  SetIsReplicated(true);

  TargetingProfile = CreateDefaultSubobject<URectangularTargetingProfile>(TEXT("TargetingProfile"));
//  TargetingProfile = CreateDefaultSubobject<UConeTargetingProfile>(TEXT("TargetingProfile"));

}


// Called when the game starts
void URobotTargetingComponent::BeginPlay()
{
  Super::BeginPlay();
  // ...

  if (ARobotGameState* RobotGameState = GetOwner()->GetWorld()->GetGameState<ARobotGameState>())
  {

    if (GetOwner()->HasAuthority())
    {

      for (AActor* Actor: RobotGameState->TargetableActors)
      {
        if (IsTargetable(Actor))
        {
          AddTargetable(Actor);
        }
      }

      RobotGameState->OnTargetableAddedDelegate.AddDynamic(this, &URobotTargetingComponent::OnTargetableRegistered);
      RobotGameState->OnTargetableRemovedDelegate.AddDynamic(this, &URobotTargetingComponent::OnTargetableUnregistered);
    }
  }
}


// Called every frame
void URobotTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//  UE_LOG(LogTemp, Warning, TEXT("%s::IsTargetAcquired"), *GetName());
  if (GetOwner()->HasAuthority())
  {
    bTargetAcquired = false;
//    Targets.Reset();
    for (AActor* Actor: Targetables)
    {
      if (IsTargeted(Actor))
      {
        Targets.AddUnique(Actor);
        bTargetAcquired = true;
      }
      else// if Targets.Contains(Actor)
      {
        Targets.Remove(Actor);
      }
//      UE_LOG(LogTemp, Warning, TEXT("%s targeting %s"), *GetName(), *Actor->GetName());
//      bTargetAcquired = bTargetAcquired || IsTargeted(Actor);
//      FString TargetAcquired = bTargetAcquired ? "True" : "False";
//      UE_LOG(LogTemp, Warning, TEXT("bTargetAcquired = %s"), *TargetAcquired);
    }
    Algo::Sort(Targets, [this](AActor* Target1, AActor* Target2)
    {
      return this->GetTargetPriority(Target1) > this->GetTargetPriority(Target2);
    });
  }
}

bool URobotTargetingComponent::IsTargetAcquired()
{
  return bTargetAcquired;
}

TArray<AActor*> URobotTargetingComponent::GetTargets()
{
  return Targets;
}

FVector URobotTargetingComponent::GetPredictedTargetLocation(AActor* Target, float DeltaTime)
{
  FVector PredictedLocation;
  if (TargetingProfile != nullptr)
  {
    PredictedLocation = TargetingProfile->GetPredictedTargetLocation(Target, DeltaTime); 
  }
  return PredictedLocation;
}

bool URobotTargetingComponent::IsTargeted(AActor* Actor) const
{
  if (TargetingProfile != nullptr)
  {
//TODO register this somewhere to avoid many casts?
    return TargetingProfile->IsTargeted(Cast<ARobotCharacter>(GetOwner()), Actor);
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
  Targets.Remove(Actor);
}

bool URobotTargetingComponent::IsTargetable(AActor* Actor) const
{
  UE_LOG(LogTemp, Warning, TEXT("%s::IsTargetable"), *GetName());
  ARobotCharacter* OwnerChar = Cast<ARobotCharacter>(GetOwner());
  ITargetableInterface* Targetable = Cast<ITargetableInterface>(Actor);
  if (Targetable != nullptr)
  {
    return Targetable->IsTargetableBy(OwnerChar);
  }

  return false;
}

float URobotTargetingComponent::GetTargetPriority(AActor* Target)
{
// distance method
//  return 1.0f/FVector::Distance(Target->GetActorLocation(),GetOwner()->GetActorLocation());
// view method
  ARobotCharacter* OwnerChar = Cast<ARobotCharacter>(GetOwner());
  FVector ToTarget = Target->GetActorLocation()-OwnerChar->GetActorLocation();
  FVector TargetDirection = ToTarget/ToTarget.Size();
  float Priority = FVector::DotProduct(TargetDirection, OwnerChar->GetActorRotation().Vector());
//  float Priority = FVector::DotProduct(TargetDirection, OwnerChar->GetViewRotation().Vector());
  UE_LOG(LogTemp, Warning, TEXT("%s Targeting Priority: %f"), *Target->GetName(), Priority);
  UE_LOG(LogTemp, Warning, TEXT("%s Target Direction Vector Size: %f"), *Target->GetName(), TargetDirection.Size());
  return Priority;
}

void URobotTargetingComponent::OnTargetableRegistered(AActor* Actor)
{
  UE_LOG(LogTemp,Warning,TEXT("%s::OnTargetableRegistered"), *GetName());
  if (GetOwner()->HasAuthority() && IsTargetable(Actor))
  {
    AddTargetable(Actor);
  }
}

void URobotTargetingComponent::OnTargetableUnregistered(AActor* Actor)
{
  UE_LOG(LogTemp,Warning,TEXT("%s::OnTargetableUnregistered"), *GetName());
  if (GetOwner()->HasAuthority())
  {
    RemoveTargetable(Actor);
  }
}

void URobotTargetingComponent::GetLifetimeReplicatedProps(TArray <FLifetimeProperty > & OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  DOREPLIFETIME(URobotTargetingComponent, bTargetAcquired);
  DOREPLIFETIME(URobotTargetingComponent, Targets);

}
