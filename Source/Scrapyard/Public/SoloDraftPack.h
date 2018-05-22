// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RobotPartAssignment.h"
#include "SoloDraftPack.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API USoloDraftPack : public UObject
{
	GENERATED_BODY()
	
public:	
	USoloDraftPack();

	URobotPartAssignment* PartAssignment;
	
};
