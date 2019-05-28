// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UI/TargetingWidget.h"
#include "Targeting/TargetingProfile.h"
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

  UPROPERTY()
  UTargetingProfile* TargetingProfile;

  bool IsTargetAcquired();

  TSubclassOf<UTargetingWidget> TargetingWidget;

  TArray<FVector> GetFaceVerts() const;

  UFUNCTION()
  void OnTargetableRegistered(AActor* Actor);
  UFUNCTION()
  void OnTargetableUnregistered(AActor* Actor);

  void AddTargetable(AActor* Actor);
  void RemoveTargetable(AActor* Actor);

  bool IsTargetable(AActor* Actor) const;

  bool IsTargeted(AActor* Actor) const;

//  float GetRange();

protected:

  // Called when the game starts
  virtual void BeginPlay() override;

  bool bTargetAcquired;
//  TArray<AActor*> Targets;

//  UPROPERTY()
  TArray<AActor*> Targetables;

// get the other actor's location relative to the owner's view rotation vector
  FVector GetLocationRelativeToView(AActor* OtherActor) const;

};
