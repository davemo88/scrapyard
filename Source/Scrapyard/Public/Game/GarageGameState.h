// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Drafting/SoloDraft.h"
#include "GarageGameState.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API AGarageGameState : public AGameStateBase
{
  GENERATED_BODY()

public:

  AGarageGameState();

  UPROPERTY()
  USoloDraft* CurrentDraft;

  virtual void BeginPlay() override;

  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
  
  void SetCurrentDraft();
  
  
};
