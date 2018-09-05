// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoloDraft.generated.h"

class URobotPartAssignment;
class URobotPart;
class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class UHandheldPart;
class UBoosterPart;
class UChipPart;

/**
 * 
 */
UCLASS(BlueprintType)
class SCRAPYARD_API USoloDraft : public UObject
{
	GENERATED_BODY()
	
	
public:
	USoloDraft();

//	UPROPERTY()
	int32 Picks = 0;

//	UPROPERTY()
	int32 MaxPicks = 24;

	UPROPERTY(BlueprintReadOnly)
	TArray<UHeadPart*> DraftedHeads;
	UPROPERTY(BlueprintReadOnly)
	TArray<UCorePart*> DraftedCores;
	UPROPERTY(BlueprintReadOnly)
	TArray<UArmsPart*> DraftedArms;
	UPROPERTY(BlueprintReadOnly)
	TArray<ULegsPart*> DraftedLegs;
	UPROPERTY(BlueprintReadOnly)
	TArray<UHandheldPart*> DraftedHandhelds;
	UPROPERTY(BlueprintReadOnly)
	TArray<UBoosterPart*> DraftedBoosters;
	UPROPERTY(BlueprintReadOnly)
	TArray<UChipPart*> DraftedChips;

	UPROPERTY(BlueprintReadOnly)
	URobotPartAssignment* CurrentPack;

// also might need to keep track of the robot(s) they built
// i.e. as a Part Assignment

};
