// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "ArmsPart.generated.h"

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

  void Draft(USoloDraft* SoloDraft);

  void Assign(URobotBodyComponent* RobotBody);
};
