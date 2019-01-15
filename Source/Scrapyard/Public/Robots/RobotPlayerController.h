// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/ScrapyardGameInstance.h"
#include "Player/ScrapyardPlayerController.h"
#include "UI/RobotHUDWidget.h"
#include "Parts/RobotPartAssignment.h"
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

  TArray< FDeferredFireInput, TInlineAllocator<2> > DeferredFireInputs;

  virtual void BeginPlay() override;

public:
  URobotHUDWidget* RobotHUDWidget;

// TODO: refector these to be protected
  virtual void OnFire();
  virtual void OnStopFire();

  ARobotPlayerController();

  virtual void Possess(APawn* InPawn) override;

  bool HasDeferredFireInputs();

  void ApplyDeferredFireInputs();

  void SetRobotCharacter(ARobotCharacter* NewRobotCharacter);

  UFUNCTION(Client, Reliable)
  void ClientGetPartAssignmentIDs();

//  UPROPERTY(Replicated)
  UPROPERTY()
  FPartAssignmentIDs PartAssignmentIDs;

private:
// want this property because otherwise we will end up casting GetPawn() to ARobotCharacter all the time
  UPROPERTY()
  ARobotCharacter* RobotCharacter;

  UFUNCTION(Server, Reliable, WithValidation)
  void ServerSetPartAssignmentIDs(FPartAssignmentIDs NewPartAssignmentIDs);

  UFUNCTION(Client, Reliable)
  void ClientSetRobotPartAssignmentFromIDs(FPartAssignmentIDs NewPartAssignmentIDs);

};
