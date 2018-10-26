// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "ArmsPart.generated.h"

class URobotPartAssignment;
/**
 * 
 */
UCLASS()
class SCRAPYARD_API UArmsPart : public URobotPart
{
  GENERATED_BODY()

public:

  UPROPERTY(EditAnywhere)
  uint16 MaxWeight;
  UPROPERTY(EditAnywhere)
  uint8 RecoilControl;

//  virtual USkeletalMesh* GetSkeletalMesh() override { return nullptr; };

  void Draft(USoloDraft* SoloDraft) override;

  void Assign(URobotPartAssignment* PartAssignment) override;

  TSoftObjectPtr<UTexture2D> GetCardIconAssetPtr();
};
