// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraActor.h"
#include "SoloDraftActor.generated.h"

class USoloDraft;
class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class ARobotPartActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextPackReadyDelegate);

UCLASS()
class SCRAPYARD_API ASoloDraftActor : public AActor
{
  GENERATED_BODY()
  
public:  
  // Sets default values for this actor's properties
  ASoloDraftActor();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UPROPERTY()
  uint32 NumChoices = 3;

  UPROPERTY()
  TArray<URobotPart*> RobotPartPool;

  void NextPack();

  void SamplePack();

  URobotPart* SamplePart(bool Replacement = true);

  UFUNCTION(Server, reliable, WithValidation)
  void ServerDraftPart(URobotPart* RobotPart);
  
  UFUNCTION()
  void OnSoloDraftWidgetReady();

  void SetupRobotPartPool();

public:  
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  FOnNextPackReadyDelegate OnNextPackReady;

};
