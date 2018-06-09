// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "HeadPart.generated.h"

class URobotPartAssignment;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UHeadPart : public URobotPart
{
	GENERATED_BODY()
	
public:

	void Draft(USoloDraft* SoloDraft);

	void Assign(URobotBodyComponent* RobotBody);
};
