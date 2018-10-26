// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "CorePart.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UCorePart : public URobotPart
{
  GENERATED_BODY()

public:

  void Draft(USoloDraft* SoloDraft) override;

  void Assign(URobotPartAssignment* PartAssignment) override;

  TSoftObjectPtr<UTexture2D> GetCardIconAssetPtr();
};
