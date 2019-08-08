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

<<<<<<< HEAD
=======
<<<<<<< Updated upstream
  UPROPERTY()
  int32 TotalPicks = 10;

  UPROPERTY()
  int32 ChoicesPerPick = 3;
  
  virtual void DraftPart(URobotPart* Part);

>>>>>>> caecc36df94501247f28bddf555caf2098a5035a
  UPROPERTY(BlueprintReadOnly)
  TArray<URobotPart*> CurrentPack;

  UPROPERTY(BlueprintReadOnly)
  TArray<URobotPart*> DraftedParts;

// for garage
  UPROPERTY(BlueprintReadOnly)
  UPartAssignment* PartAssignment;
=======
  TArray<TSubclassOf<URobotPart>> GetPickTypes();
  
  URobotPart* SamplePart(TSubclassOf<URobotPart> PickType);

  TArray<URobotPart*> SamplePack();

protected:

  UPROPERTY()
  TArray<TSubclassOf<URobotPart>> PickTypes;

  void InitPickTypes();

  TSubclassOf<URobotPart> SamplePickType();

  UPROPERTY()
  TArray<URobotPart*> RobotPartPool;

  void InitRobotPartPool();
>>>>>>> Stashed changes

  TArray<TSubclassOf<URobotPart>> GetPickTypes();
  
  URobotPart* SamplePart(TSubclassOf<URobotPart> PickType);

  TArray<URobotPart*> SamplePack();

protected:

  UPROPERTY()
  TArray<TSubclassOf<URobotPart>> PickTypes;

  void InitPickTypes();

  TSubclassOf<URobotPart> SamplePickType();

  UPROPERTY()
  TArray<URobotPart*> RobotPartPool;

  void InitRobotPartPool();

};
