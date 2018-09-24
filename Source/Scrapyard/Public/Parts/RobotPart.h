// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Ability/ScrapyardAbility.h"
#include "RobotPart.generated.h"

class URobotPartAssets;
class UMaterial;
class USkeletalMesh;
class UManufacturer;
class URarity;
class USoloDraft;
class URobotBodyComponent;

/**
 * 
 */
UCLASS(BlueprintType)
class SCRAPYARD_API URobotPart : public USkeletalMeshComponent
{
  GENERATED_BODY()

public:

  virtual void BeginPlay() override;
  
// stats
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FString PartName;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UManufacturer* Manufacturer;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  URarity* Rarity;
// this integer type because only uint8 and int32 are supported by blueprints
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 Mass;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 PowerDrain;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 Durability;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 BallisticDefense;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int32 EnergyDefense;

  UPROPERTY()
  AScrapyardAbility* PartAbililty = NULL;

// skeletal mesh 
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UMaterial* MajorMaterial;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UMaterial* MinorMaterial;
  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UMaterial* AccentMaterial;

  virtual void Draft(USoloDraft* SoloDraft) {};

  virtual void Assign(URobotBodyComponent* RobotBody) { UE_LOG(LogTemp, Warning, TEXT("RobotPart.Assign(RobotBodyComponent)")); };

  URobotPartAssets* GetRobotPartAssets();

  virtual USkeletalMesh* GetSkeletalMesh();

};
