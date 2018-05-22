// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HeadPart.h"
#include "CorePart.h"
#include "ArmsPart.h"
#include "LegsPart.h"
#include "RobotPartHelper.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotPartHelper : public UObject
{
	GENERATED_BODY()

public:

//	URobotPartHelper();
	
private:

	UPROPERTY()
	FString HeadPath = FString(TEXT("/Game/Parts/Head"));
	UPROPERTY()
	FString CorePath = FString(TEXT("/Game/Parts/Core"));
	UPROPERTY()
	FString ArmsPath = FString(TEXT("/Game/Parts/Arms"));
	UPROPERTY()
	FString LegsPath = FString(TEXT("/Game/Parts/Legs"));


	template <typename T>
	TArray<T*> GetAllPartsInFolder(FString Path);

public:

	TArray<UHeadPart*> GetAllHeads();
	TArray<UCorePart*> GetAllCores();
	TArray<UArmsPart*> GetAllArms();
	TArray<ULegsPart*> GetAllLegs();

};
