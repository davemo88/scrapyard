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

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  FOnNextPackReadyDelegate OnNextPackReady;
  
  UPROPERTY()
  USoloDraft* CurrentDraft;

  UFUNCTION(Server, reliable, WithValidation)
  void ServerDraftPart(URobotPart* RobotPart);

protected:

<<<<<<< HEAD
  void SetCurrentDraft();

=======
>>>>>>> caecc36df94501247f28bddf555caf2098a5035a
  void NextPack();

  UFUNCTION(Server, reliable, WithValidation)
  void ServerDraftPart(URobotPart* RobotPart);
  
};
