// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UI/TargetingWidget.h"
#include "RobotTargetingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCRAPYARD_API URobotTargetingComponent : public USceneComponent
{
  GENERATED_BODY()

public:  
  // Sets default values for this component's properties
  URobotTargetingComponent();
  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  bool IsTargetAcquired();

  TSubclassOf<UTargetingWidget> TargetingWidget;

  virtual float GetRange();

  virtual TArray<FVector> GetFaceVerts();

protected:

  // Called when the game starts
  virtual void BeginPlay() override;

  bool bTargetAcquired;

//  ARobotCharacter* TargetCharacter;

  virtual bool IsTargetable(AActor* OtherActor);

  float Range;

  TArray<FVector> FaceVerts;

};
