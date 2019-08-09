// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scrapyard.h"
#include "Scrapyard.h"
#include "UObject/NoExportTypes.h"
#include "Parts/PartAssignment.h"
#include "DraftBase.generated.h"

class URobotPart;
class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class UHandheldPart;
class UBoosterPart;
class UChipPart;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UDraftBase : public UObject
{
  GENERATED_BODY()
  
public:

  UDraftBase();

  UPROPERTY()
  int32 TotalPicks;

  UPROPERTY()
  int32 CurrentPick;

  UPROPERTY()
  int32 PackSize;

  UPROPERTY()
  TArray<URobotPart*> CurrentPack;

  UPROPERTY()
  TArray<UHeadPart*> DraftedHeads;

  UPROPERTY()
  TArray<UCorePart*> DraftedCores;

  UPROPERTY()
  TArray<UArmsPart*> DraftedArms;

  UPROPERTY()
  TArray<ULegsPart*> DraftedLegs;

  UPROPERTY()
  TArray<UBoosterPart*> DraftedBoosters;

  UPROPERTY()
  TArray<UHandheldPart*> DraftedHandhelds;

  UPROPERTY()
  TArray<UChipPart*> DraftedChips;

  UPROPERTY()
  UPartAssignment* PartAssignment;
  
  virtual URobotPart* SamplePart();

  virtual void SamplePack();

  virtual void DraftPart(URobotPart* RobotPart);

  TArray<URobotPart*> GetAllDraftedParts();

protected:

  UPROPERTY()
  TArray<URobotPart*> RobotPartPool;

  virtual void InitRobotPartPool();
  
};
