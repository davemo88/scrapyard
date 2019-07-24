// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoloDraft.generated.h"

class URobotPart;
class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class UHandheldPart;
class UBoosterPart;
class UChipPart;
class UPartAssignment;

/**
 * 
 */
UCLASS(BlueprintType)
class SCRAPYARD_API USoloDraft : public UObject
{
  GENERATED_BODY()
  
  
public:
  USoloDraft();

  UPROPERTY()
  int32 TotalPicks = 10;

// TODO: which pick you're on
  UPROPERTY()
  int32 Pick = 1;

  UPROPERTY()
  int32 ChoicesPerPick = 3;

  UPROPERTY(BlueprintReadOnly)
  TArray<URobotPart*> DraftedHeads;
  UPROPERTY(BlueprintReadOnly)
  TArray<URobotPart*> DraftedCores;
  UPROPERTY(BlueprintReadOnly)
e TArray<URobotPart*> DraftedArms;
  UPROPERTY(BlueprintReadOnly)
  TArray<URobotPart*> DraftedLegs;
  UPROPERTY(BlueprintReadOnly)
  TArray<URobotPart*> DraftedHandhelds;
  UPROPERTY(BlueprintReadOnly)
  TArray<URobotPart*> DraftedBoosters;
  UPROPERTY(BlueprintReadOnly)
  TArray<URobotPart*> DraftedChips;
  
  virtual void DraftPart(URobotPart* Part);

  UPROPERTY(BlueprintReadOnly)
  TArray<URobotPart*> CurrentPack;

  UPROPERTY(BlueprintReadOnly)
  TArray<URobotPart*> DraftedParts;

// for garage
  UPROPERTY(BlueprintReadOnly)
  UPartAssignment* PartAssignment;

};
