// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Robots/RobotTargetingComponent.h"
#include "Components/BoxComponent.h"
#include "BoxTargetingComponent.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UBoxTargetingComponent : public URobotTargetingComponent
{
  GENERATED_BODY()

public:

  UBoxTargetingComponent();

  UPROPERTY(EditAnywhere)
  UBoxComponent* BoxComponent;

  FVector GetBoxFaceCenter();

  TArray<FVector> GetBoxFaceVertices();

  UFUNCTION()
  void OnBoxBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
  
  UFUNCTION()
  void OnBoxEndOverlap( class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
	
};
