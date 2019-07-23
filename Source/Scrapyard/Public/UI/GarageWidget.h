// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "UI/InstalledPartWidget.h"
#include "Parts/PartAssignment.h"
#include "GarageWidget.generated.h"

class UYourPartsWidget;
class URobotStatsWidget;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UGarageWidget : public UUserWidget
{
  GENERATED_BODY()

public:

    void SetInstalledParts(UPartAssignment* PartAssignment);

//TODO: maybe proper methods to modify these?  
  UPROPERTY(meta=(BindWidget))
  URobotStatsWidget* RobotStatsWidget;

  UPROPERTY(meta=(BindWidget))
  UYourPartsWidget* YourPartsWidget;

  UPROPERTY(meta=(BindWidget))
  UButton* RobotTestButton;

  UPROPERTY(meta=(BindWidget))
  UButton* BattleButton;

  UPROPERTY(meta=(BindWidget))
  UInstalledPartWidget* InstalledHeadWidget;

  UPROPERTY(meta=(BindWidget))
  UInstalledPartWidget* InstalledCoreWidget;

  UPROPERTY(meta=(BindWidget))
  UInstalledPartWidget* InstalledArmsWidget;

  UPROPERTY(meta=(BindWidget))
  UInstalledPartWidget* InstalledLegsWidget;

  UPROPERTY(meta=(BindWidget))
  UInstalledPartWidget* InstalledRightHandheldWidget;


};
