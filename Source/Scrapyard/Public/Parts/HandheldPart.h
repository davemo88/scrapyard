// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "HandheldPart.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UHandheldPart : public URobotPart
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	int32 Attack = 0;

// milliseconds
	UPROPERTY(EditAnywhere)
	int32 Cooldown = 0;

	void Draft(USoloDraft* SoloDraft);

};
