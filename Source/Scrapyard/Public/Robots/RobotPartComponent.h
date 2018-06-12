// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Parts/RobotPart.h"
#include "RobotPartComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SCRAPYARD_API URobotPartComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:

	void AssignPart(URobotPart* Part);

protected:

	URobotPart* AssignedPart;

};
