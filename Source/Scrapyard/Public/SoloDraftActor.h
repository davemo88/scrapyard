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

  TArray<UHeadPart*> HeadParts;
  TArray<UCorePart*> CoreParts;
  TArray<UArmsPart*> ArmsParts;
  TArray<ULegsPart*> LegsParts;

  void SpawnDraftCamera();

  ARobotPartActor* SpawnRobotPartActor(
    URobotPart* RobotPart,
//    TSubclassOf<URobotPart> RobotPartClass,
    FVector Loc = FVector(0.0f, 0.0f, 0.0f),
    FRotator Rot = FRotator(0.0f, 0.0f, 0.0f),
    FActorSpawnParameters SpawnParams = FActorSpawnParameters()
  );

  void NextPack();

  void SamplePack();

  template<typename T>
  T* SamplePart(TArray<T*>& Parts, bool Replacement = true);

  UFUNCTION(Server, reliable, WithValidation)
  void ServerDraftPart(URobotPart* RobotPart);
  
  UFUNCTION()
  void OnSoloDraftWidgetReady();

public:  
  // Called every frame
  virtual void Tick(float DeltaTime) override;

//TODO needs to be uproperty or attributes get GC'ed ??
//  UPROPERTY()
//  USoloDraft* CurrentDraft;

  FOnNextPackReadyDelegate OnNextPackReady;

};
