// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoloDraft.generated.h"

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
//	TArray<UHeadPart*> DraftedHeads;
	TArray<TSubclassOf<UHeadPart>> DraftedHeads;
	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf<UCorePart>> DraftedCores;
	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf<UArmsPart>> DraftedArms;
	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf<ULegsPart>> DraftedLegs;
	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf<UHandheldPart>> DraftedHandhelds;
	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf<UBoosterPart>> DraftedBoosters;
	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf<UChipPart>> DraftedChips;

	UPROPERTY(BlueprintReadOnly)
//        TArray<TSubclassOf<URobotPart>> CurrentPack;
        TArray<URobotPart*> CurrentPack;

};
