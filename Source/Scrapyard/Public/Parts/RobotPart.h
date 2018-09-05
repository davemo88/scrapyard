// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RobotPart.generated.h"

class UMaterial;
class USkeletalMesh;
class UManufacturer;
class URarity;
class USoloDraft;
class URobotPartAssignment;
class URobotBodyComponent;

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

	virtual void Assign(URobotPartAssignment* PartAssignment) { UE_LOG(LogTemp, Warning, TEXT("RobotPart.Assign(PartAssignment)")); };

	virtual void Assign(URobotBodyComponent* RobotBody) { UE_LOG(LogTemp, Warning, TEXT("RobotPart.Assign(RobotBodyComponent)")); };

};
