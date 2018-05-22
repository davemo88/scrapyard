// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RobotStats.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotStats : public UObject
{
	GENERATED_BODY()

public:
	URobotStats() {};
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Mass = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxDurability = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxPower = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BallisticDefense = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnergyDefense = 0;
};
