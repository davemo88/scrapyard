// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ScrapyardPlayerController.generated.h"

class URobotHUDWidget;

struct FDeferredFireInput
{
  uint8 FireMode;
// if true call StartFire(), false call StopFire()
  bool bStartFire;

  FDeferredFireInput(uint8 FireModeArg, bool bStartFireArg)
    : FireMode(FireModeArg), bStartFire(bStartFireArg)
  {}
};
/**
 * 
 */
UCLASS()
class SCRAPYARD_API AScrapyardPlayerController : public APlayerController
{
  GENERATED_BODY()

private:

  UPROPERTY()
  ARobotCharacter* RobotCharacter;

protected:
  virtual void BeginPlay() override;

  void SetupRobotHUDWidget();

  URobotHUDWidget* RobotHUDWidget;

// see UnrealTournament firing implementation
  bool bFirePressed;
  virtual void OnFire();

  TArray< FDeferredFireInput, TInlineAllocator<2> > DeferredFireInputs;

public:
  bool HasDeferredFireInputs();

  void ApplyDeferredFireInputs();
};
