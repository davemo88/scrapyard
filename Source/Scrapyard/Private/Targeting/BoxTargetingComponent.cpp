// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxTargetingComponent.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotBodyComponent.h"

UBoxTargetingComponent::UBoxTargetingComponent()
{

  BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
  BoxComponent->SetupAttachment(this);
  BoxComponent->SetBoxExtent(FVector(1000.0f,100.0f,100.0f));
  BoxComponent->SetRelativeLocation(FVector(1000.0f,0.0f,0.0f));
  BoxComponent->SetHiddenInGame(false);

  BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UBoxTargetingComponent::OnBoxBeginOverlap);
  BoxComponent->OnComponentEndOverlap.AddDynamic(this, &UBoxTargetingComponent::OnBoxEndOverlap);
}

//TODO: add flag for relative / world location
TArray<FVector> UBoxTargetingComponent::GetBoxFaceVertices()
{
  TArray<FVector> Vertices;

  FVector Extent = BoxComponent->GetScaledBoxExtent();
//  FVector Extent = RelativeRotation.RotateVector(TargetingBoxComponent->GetScaledBoxExtent());
//  FVector Extent = TargetingBoxComponent->GetUnscaledBoxExtent();
//  UE_LOG(LogTemp, Warning, TEXT("Box Extent: %s"), *Extent.ToString());

//  Vertices.Add(FVector(Extent.X * 2, Extent.Y * -0.5f, Extent.Z));
//  Vertices.Add(FVector(Extent.X * 2, Extent.Y * 0.5f, Extent.Z));
//  Vertices.Add(FVector(Extent.X * 2, Extent.Y * 0.5f, 0.0f));
//  Vertices.Add(FVector(Extent.X * 2, Extent.Y * -0.5f, 0.0f));

  Vertices.Add(FVector(Extent.X * 2, -Extent.Y, Extent.Z));
  Vertices.Add(FVector(Extent.X * 2, Extent.Y, Extent.Z));
  Vertices.Add(FVector(Extent.X * 2, Extent.Y, -Extent.Z));
  Vertices.Add(FVector(Extent.X * 2, -Extent.Y, -Extent.Z));
  Vertices.Add(FVector(Extent.X * 0.5, -Extent.Y, Extent.Z));
  Vertices.Add(FVector(Extent.X * 0.5, Extent.Y, Extent.Z));
  Vertices.Add(FVector(Extent.X * 0.5, Extent.Y, -Extent.Z));
  Vertices.Add(FVector(Extent.X * 0.5, -Extent.Y, -Extent.Z));

//  Vertices.Add(FVector(Extent.X, -Extent.Y, Extent.Z));
//  Vertices.Add(FVector(Extent.X, Extent.Y, Extent.Z));
//  Vertices.Add(FVector(Extent.X, Extent.Y, 0.0f));
//  Vertices.Add(FVector(Extent.X, -Extent.Y, 0.0f));

  return Vertices;
}

//TODO: add flag for relative / world location
FVector UBoxTargetingComponent::GetBoxFaceCenter()
{
  FVector Extent = BoxComponent->GetScaledBoxExtent();

//  UE_LOG(LogTemp, Warning, TEXT("%s"), *Extent.ToString());

  FVector FaceCenter = FVector(Extent.X * 2, 0.0f, 0.0f);

  return FaceCenter;

//  return RelativeRotation.RotateVector(FVector(Extent.X * 0.5f, Extent.Y, Extent.Z * 0.5));
}

void UBoxTargetingComponent::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnBoxBeginOverlap"), *GetName());
//TODO: this should be done using channels i bet
  if (ARobotCharacter* OtherChar = Cast<ARobotCharacter>(OtherActor))
  {
    if (OtherChar != GetOwner() && (Cast<URobotBodyComponent>(OtherComponent) != nullptr))
    {
      UE_LOG(LogTemp, Warning, TEXT("%s::OnBoxBeginOverlap - %s Target Acquired"), *GetName(), *OtherComponent->GetName());
      bTargetAcquired = true;
    }
  }
}
  
void UBoxTargetingComponent::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnTargetingBoxEndOverlap"), *GetName());
  if (ARobotCharacter* OtherChar = Cast<ARobotCharacter>(OtherActor))
  {
    if (OtherChar != GetOwner() && (Cast<URobotBodyComponent>(OtherComponent) != nullptr))
    {
      UE_LOG(LogTemp, Warning, TEXT("%s::OnBoxBeginOverlap - Target Lost"), *GetName());
      bTargetAcquired = false;
    }
  }
}


