// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScrapyardDefaultAssets.generated.h"

// do we need do to a lot of forward declarations here
// since this will be an attribute of the Game Instance
// and many related classes might include the Game Instance?
class UMainMenuWidget;
class UEscapeMenuWidget;
class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;


/**
 * 
 */
UCLASS(Blueprintable)
class SCRAPYARD_API UScrapyardDefaultAssets : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMainMenuWidget> MainMenuWidgetBP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UEscapeMenuWidget> EscapeMenuWidgetBP;

	UPROPERTY(EditDefaultsOnly)
	UHeadPart* DefaultHeadPart;
	
	UPROPERTY(EditDefaultsOnly)
	UCorePart* DefaultCorePart; 
	
	UPROPERTY(EditDefaultsOnly)
	UArmsPart* DefaultArmsPart;

	UPROPERTY(EditDefaultsOnly)
	ULegsPart* DefaultLegsPart;

	UPROPERTY(EditDefaultsOnly)
	FString TestString;


	
};
