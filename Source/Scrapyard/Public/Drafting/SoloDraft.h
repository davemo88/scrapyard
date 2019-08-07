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

  UPROPERTY()
  int32 ChoicesPerPick = 3;
  
  virtual void DraftPart(URobotPart* Part);

  UPROPERTY(BlueprintReadOnly)
  TArray<URobotPart*> CurrentPack;

  UPROPERTY(BlueprintReadOnly)
  TArray<URobotPart*> DraftedParts;

  UPROPERTY(BlueprintReadOnly)
  UPartAssignment* PartAssignment;

};
