// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ScrapyardPlayerController.h"
#include "RobotPlayerController.generated.h"

class ARobotCharacter;

struct FDeferredFireInput
{
  uint8 FireMode;
  bool bStartFire;

  FDeferredFireInput(uint8 FireModeArg, bool bStartFireArg)
    : FireMode(FireModeArg), bStartFire(bStartFireArg)
  {}
};

UCLASS(config=Game)
class SCRAPYARD_API ARobotPlayerController : public AScrapyardPlayerController
{
  GENERATED_BODY()

protected:

// see UnrealTournament firing implementation
  bool bFirePressed;
  virtual void OnFire();
  virtual void OnStopFire();

  TArray< FDeferredFireInput, TInlineAllocator<2> > DeferredFireInputs;

public:

  ARobotPlayerController();

  virtual void Possess(APawn* InPawn) override;

  virtual void SetupInputComponent() override;

  UFUNCTION(Client, Reliable)
  void ClientSetupInputComponent();

  bool HasDeferredFireInputs();

  void ApplyDeferredFireInputs();

private:
  UPROPERTY()
  ARobotCharacter* RobotCharacter;

};
