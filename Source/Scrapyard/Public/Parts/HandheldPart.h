// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "HandheldPart.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UHandheldPart : public URobotPart
{
  GENERATED_BODY()

public:

  static UHandheldPart* NewHandheld(uint32 NewPartID, FText NewPartName, UManufacturer* NewManufacturer, URarity* NewRarity, uint32 NewMass, uint32 NewPowerDrain, uint32 NewAttack, float NewCooldown, TSubclassOf<AScrapyardAbility> NewAbilityClass, TSoftObjectPtr<USkeletalMesh> NewSkeletalMesh, TSoftObjectPtr<UMaterial> NewMajorMaterial);

  UPROPERTY(EditAnywhere)
  int32 Attack = 0;

// milliseconds
  UPROPERTY(EditAnywhere)
  float Cooldown = 0.0f;

  virtual void Assign(UPartAssignment* PartAssignment) override;

  virtual bool IsAssignedTo(UPartAssignment* PartAssignment) override;

  UTexture2D* GetPartTypeIcon() const override;

//  TArray<FStatText> GetStatsText() const override;

};
