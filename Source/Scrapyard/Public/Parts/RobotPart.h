// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkeletalMeshTypes.h"
#include "Materials/Material.h"
#include "Engine/DataAsset.h"
#include "Parts/Manufacturer.h"
#include "Parts/Rarity.h"
#include "RobotPart.generated.h"

class USoloDraft;
/**
 * 
 */
UCLASS(BlueprintType)
class SCRAPYARD_API URobotPart : public UDataAsset
{
	GENERATED_BODY()

public:
	
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

// skeletal mesh 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial* MajorMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial* MinorMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial* AccentMaterial;

	virtual void Draft(USoloDraft* SoloDraft) {};
};