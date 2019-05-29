// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Targeting/TargetableComponent.h"
#include "Targeting/TargetableInterface.h"
#include "Drone.generated.h"

UCLASS()
class SCRAPYARD_API ADrone : public AActor, public ITargetableInterface
{
  GENERATED_BODY()
  
public:  
  // Sets default values for this actor's properties
  ADrone();

// Called every frame
  virtual void Tick(float DeltaTime) override;

// Targetable Interface
  virtual bool IsTargetableBy(ARobotCharacter* Robot) override;

  UPROPERTY(EditAnywhere)
  int32 Team;

  UPROPERTY()
  UTargetableComponent* TargetableComponent;

  UPROPERTY(EditAnywhere)
  UStaticMeshComponent* StaticMeshComponent;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

};
