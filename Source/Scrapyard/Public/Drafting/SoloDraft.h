// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drafting/DraftBase.h"
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
class SCRAPYARD_API USoloDraft : public UDraftBase
{
  GENERATED_BODY()
  
public:

  USoloDraft();
  
  virtual URobotPart* SamplePart() override;

  virtual void DraftPart(URobotPart* RobotPart) override;

protected:

  UPROPERTY()
  TArray<TSubclassOf<URobotPart>> MissingTypes;

  void InitMissingTypes();

};
