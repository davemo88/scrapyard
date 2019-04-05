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

  UPROPERTY(EditAnywhere)
  UTargetingProfile* TargetingProfile;

  bool IsTargetAcquired();

  TSubclassOf<UTargetingWidget> TargetingWidget;

//  virtual FVector GetTargetingOffset();
//

  TArray<FVector> GetFaceVerts();

  void AddTargetable(AActor* Targetable);
  void RemoveTargetable(AActor* Targetable);

  bool IsTargetable(AActor* Actor);

  bool IsTargeted(AActor* Actor);

//  float GetRange();

protected:

  // Called when the game starts
  virtual void BeginPlay() override;

  bool bTargetAcquired;

  TArray<AActor*> Targetables;
//  TArray<AActor*> Targets;
//
  FVector GetLocationRelativeToView(AActor* OtherActor);

};
