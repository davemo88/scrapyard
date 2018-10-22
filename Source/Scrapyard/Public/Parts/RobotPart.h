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
//

  URobotPart();
  
  UPROPERTY(BlueprintReadOnly)
  FString PartName;
  UPROPERTY(BlueprintReadOnly)
  UManufacturer* Manufacturer;
  UPROPERTY(BlueprintReadOnly)
  URarity* Rarity;
  UPROPERTY(BlueprintReadOnly)
  UTexture2D* CardIcon;

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

  void OnSkeletalMeshLoaded();

  UMaterial* GetMajorMaterial();

  void OnMajorMaterialLoaded();

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

  UManufacturer* GetManufacturer();

  void OnManufacturerLoaded();

  UTexture2D* GetCardIcon();

  void OnCardIconLoaded();

protected: 

  virtual TSoftObjectPtr<USkeletalMesh> GetSkeletalMeshAssetPtr() { return nullptr; };

  virtual TSoftObjectPtr<UMaterial> GetMajorMaterialAssetPtr() { return nullptr; };

  virtual TSoftObjectPtr<UManufacturer> GetManufacturerAssetPtr() { return nullptr; };

  virtual TSoftObjectPtr<UTexture2D> GetCardIconAssetPtr() { return nullptr; };

};
