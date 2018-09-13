// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RobotPartAssignment.generated.h"

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
class SCRAPYARD_API URobotPartAssignment : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHeadPart* Head = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCorePart* Core = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArmsPart* Arms = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULegsPart* Legs = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoosterPart* BoosterPart = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHandheldPart* RightHandheld = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHandheldPart* LeftHandheld = nullptr;

// TODO: remove when we have proper character init
	UFUNCTION(BlueprintCallable)
	bool IsComplete();

	void UnassignAll();

	void SetDefaultAssignment();
};
