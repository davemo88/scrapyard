// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/RobotPart.h"
#include "WeaponPart.generated.h"

namespace EDamageType
{
	enum Type
	{
		Kinetic,
		Electromagnetic,
		Thermal,
	};
}

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UWeaponPart : public URobotPart
{
	GENERATED_BODY()

	EDamageType::Type DamageType;
};
