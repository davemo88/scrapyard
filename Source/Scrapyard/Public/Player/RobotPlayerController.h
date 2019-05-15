// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/ScrapyardGameInstance.h"
#include "Player/ScrapyardPlayerController.h"
#include "UI/RobotHUDWidget.h"
#include "UI/MatchTimerWidget.h"
#include "UI/RobotTunerWidget.h"
#include "Parts/PartAssignment.h"
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

public:

  virtual void Tick(float DeltaTime) override;

  URobotHUDWidget* RobotHUDWidget;

  UMatchTimerWidget* MatchTimerWidget;
  void SetupMatchTimerWidget();

  virtual void OnFire();
  virtual void OnStopFire();

  ARobotPlayerController();

  bool HasDeferredFireInputs();

  void ApplyDeferredFireInputs();

  void SetRobotCharacter(ARobotCharacter* NewRobotCharacter);

  ARobotCharacter* GetRobotCharacter();

  UFUNCTION(Client, Reliable)
  void ClientGetPartAssignmentIDs();

//  UPROPERTY(Replicated)
  UPROPERTY()
  FPartAssignmentIDs PartAssignmentIDs;

  UFUNCTION(Server, Reliable, WithValidation)
  void ServerNotifyGameStateReplicated();

  bool IsGameStateReplicated();

  void SetNewTune(FRobotTuneParams TuneParams);

  UFUNCTION(Server, WithValidation, Reliable)
  void ServerSetNewTune(FRobotTuneParams TuneParams);

  void ApplyTuneParams(FRobotTuneParams TuneParams);

protected:
  virtual void OnPossess(APawn* InPawn) override;

  virtual void BeginPlay() override;

// want this property because otherwise we will end up casting GetPawn() to ARobotCharacter all the time
  UPROPERTY()
  ARobotCharacter* RobotCharacter;

  UFUNCTION(Server, Reliable, WithValidation)
  void ServerSetPartAssignmentIDs(FPartAssignmentIDs NewPartAssignmentIDs);

// see UnrealTournament firing implementation
  bool bFirePressed;

  TArray< FDeferredFireInput, TInlineAllocator<2> > DeferredFireInputs;

  bool bGameStateReplicated;


};
