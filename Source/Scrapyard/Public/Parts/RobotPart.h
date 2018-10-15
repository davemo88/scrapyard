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
  
  UPROPERTY(BlueprintReadOnly)
  FString PartName;
  UPROPERTY(BlueprintReadOnly)
  UManufacturer* Manufacturer;
  UPROPERTY(BlueprintReadOnly)
  URarity* Rarity;
// this integer type because only uint8 and int32 are supported by blueprints
  UPROPERTY(BlueprintReadOnly)
  int32 Mass;
  UPROPERTY(BlueprintReadOnly)
  int32 PowerDrain;
  UPROPERTY(BlueprintReadOnly)
  int32 Durability;
  UPROPERTY(BlueprintReadOnly)
  int32 BallisticDefense;
  UPROPERTY(BlueprintReadOnly)
  int32 EnergyDefense;

  UPROPERTY(BlueprintReadOnly)
  TSubclassOf<AScrapyardAbility> AbilityClass;

// skeletal mesh 
// maybe this should be a TAssetPtr, but I think just the thing on the asset blueprint needs to be a TAssetPtr ? ? 
  UPROPERTY(BlueprintReadOnly)
  USkeletalMesh* SkeletalMesh;

  void SetSkeletalMesh();

  USkeletalMesh* GetSkeletalMesh();

  void OnSkeletalMeshAssetLoaded();

  UPROPERTY(BlueprintReadOnly)
  UMaterial* MajorMaterial;
  UPROPERTY(BlueprintReadOnly)
  UMaterial* MinorMaterial;
  UPROPERTY(BlueprintReadOnly)
  UMaterial* AccentMaterial;

  virtual void Draft(USoloDraft* SoloDraft) {};

  virtual void Assign(URobotBodyComponent* RobotBody) { UE_LOG(LogTemp, Warning, TEXT("RobotPart.Assign(RobotBodyComponent)")); };

//  virtual void Assign(URobotPartAssignment* RobotPartAssignment);

  static URobotPartAssets* RobotPartAssetsBP;

protected: 

  virtual TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() { return nullptr; };
};
