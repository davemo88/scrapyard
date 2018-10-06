// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScrapyardDefaultAssets.generated.h"

class UMainMenuWidget;
class UEscapeMenuWidget;
class UGarageWidget;
class USoloDraftWidget;
class UPartCardWidget;
class URobotHUDWidget;

class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class UHandheldPart;

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
  TSubclassOf<class UGarageWidget> GarageWidgetBP;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class USoloDraftWidget> SoloDraftWidgetBP;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class UPartCardWidget> PartCardWidgetBP;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<class URobotHUDWidget> RobotHUDWidgetBP;

};
