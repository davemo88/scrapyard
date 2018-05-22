// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartHelper.h"
#include "AssetRegistryModule.h"
#include "EngineUtils.h"

//URobotPartHelper::URobotPartHelper()
//{
//	FString HEADS_PATH = FString(TEXT("/Game/Parts/Head"));
//	FString CORES_PATH = "/Game/Parts/Core";
//	FString ARMS_PATH = "/Game/Parts/Arms";
//	FString LEGS_PATH = "/Game/Parts/Legs";
//}

template <typename T>
TArray<T*> URobotPartHelper::GetAllPartsInFolder(FString Path)
{
	TArray<UObject*> Assets;
//	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Parts/Head"), Assets, EngineUtils::ATL_Regular);
	
	UE_LOG(LogTemp, Warning, TEXT("path is: %s"), *Path);
	bool Result = EngineUtils::FindOrLoadAssetsByPath(Path, Assets, EngineUtils::ATL_Regular);
	if (Result) {
		UE_LOG(LogTemp, Warning, TEXT("got this many assets: %i"), Assets.Num());
	}

	TArray<T*> Parts;
	for (UObject* Asset : Assets)
	{
		T* Part = Cast<T>(Asset);
		if (Part)
		{
			Parts.Add(Part);
		}
		else
		{
			// probably abort cause something's wrong
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("got this many parts: %i"), Parts.Num());

	return Parts;
}

TArray<UHeadPart*> URobotPartHelper::GetAllHeads()
{
	return GetAllPartsInFolder<UHeadPart>(HeadPath);
}

TArray<UCorePart*> URobotPartHelper::GetAllCores()
{
	return GetAllPartsInFolder<UCorePart>(CorePath);
}

TArray<UArmsPart*> URobotPartHelper::GetAllArms()
{
	return GetAllPartsInFolder<UArmsPart>(ArmsPath);
}

TArray<ULegsPart*> URobotPartHelper::GetAllLegs()
{
	return GetAllPartsInFolder<ULegsPart>(LegsPath);
}
