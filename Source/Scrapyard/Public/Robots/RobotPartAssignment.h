// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/HandheldPart.h"
#include "RobotPartAssignment.generated.h"

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
	UHandheldPart* RightHandheldPart = nullptr;

	UFUNCTION(BlueprintCallable)
	bool IsComplete();

	UFUNCTION()
	void UnassignAll();
};