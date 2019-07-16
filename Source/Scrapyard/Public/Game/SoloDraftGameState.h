// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SoloDraftGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextPackReadyDelegate);

class USoloDraft;
/**
 * 
 */
UCLASS()
class SCRAPYARD_API ASoloDraftGameState : public AGameStateBase
{
  GENERATED_BODY()

public:

  ASoloDraftGameState();

  FOnNextPackReadyDelegate OnNextPackReady;
  
  UPROPERTY()
  USoloDraft* CurrentDraft;

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
  
};
