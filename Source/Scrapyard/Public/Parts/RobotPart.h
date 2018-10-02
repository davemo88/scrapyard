// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RobotPart.generated.h"

class UManufacturer;
class URarity;
class USoloDraft;
class URobotBodyComponent;
class URobotPartAssets;
class AScrapyardAbility;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotPart : public UObject
{
  GENERATED_BODY()

public:
// stats
  
  UPROPERTY()
  FString PartName;
  UPROPERTY()
  UManufacturer* Manufacturer;
  UPROPERTY()
  URarity* Rarity;
// this integer type because only uint8 and int32 are supported by blueprints
  UPROPERTY()
  int32 Mass;
  UPROPERTY()
  int32 PowerDrain;
  UPROPERTY()
  int32 Durability;
  UPROPERTY()
  int32 BallisticDefense;
  UPROPERTY()
  int32 EnergyDefense;

  UPROPERTY()
  TSubclassOf<AScrapyardAbility> AbilityClass;

// skeletal mesh 
// maybe this should be a TAssetPtr, but I think just the thing on the asset blueprint needs to be a TAssetPtr ? ? 
  UPROPERTY(BlueprintReadOnly)
  USkeletalMesh* SkeletalMesh;

  UPROPERTY(BlueprintReadOnly)
  UMaterial* MajorMaterial;
  UPROPERTY(BlueprintReadOnly)
  UMaterial* MinorMaterial;
  UPROPERTY(BlueprintReadOnly)
  UMaterial* AccentMaterial;

  virtual void Draft(USoloDraft* SoloDraft) {};

  virtual void Assign(URobotBodyComponent* RobotBody) { UE_LOG(LogTemp, Warning, TEXT("RobotPart.Assign(RobotBodyComponent)")); };
//  virtual void Assign(URobotPartAssignment* RobotPartAssignment);

  URobotPartAssets* GetRobotPartAssets();

  virtual USkeletalMesh* GetSkeletalMesh();
};
