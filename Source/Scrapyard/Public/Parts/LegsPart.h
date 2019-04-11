// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "LegsPart.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ULegsPart : public URobotPart
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintReadOnly)
  int32 MaxWeight;

  UPROPERTY(BlueprintReadOnly)
  int32 MovementSpeed;

  UPROPERTY(BlueprintReadOnly)
  int32 Stability;

  void Draft(USoloDraft* SoloDraft) override;

  void Assign(URobotPartAssignment* PartAssignment) override;

  virtual TArray<FStatText> GetStatsText() const override;

protected:

  TSoftObjectPtr<UTexture2D> GetCardIconAssetPtr();
};
