// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/TargetingWidget.h"
#include "Components/CanvasPanel.h"
#include "RobotHUDWidget.generated.h"

class ARobotCharacter;
class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotHUDWidget : public UUserWidget
{
  GENERATED_BODY()

public:

  void SetRobotCharacter(ARobotCharacter* NewRobotCharacter);

protected:

  void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override; 

  UFUNCTION()
  void UpdatePowerBar();
  UFUNCTION()
  void UpdateHitPoints();
  UFUNCTION()
  void UpdateSpeed();
  UFUNCTION()
  void UpdateWeaponName();

  UFUNCTION()
  void UpdateTargetingWidget();

//  UFUNCTION()
//  void SetHitPointsText(FText NewHitPointsText);

  UPROPERTY()
  ARobotCharacter* RobotCharacter;

  UPROPERTY(meta=(BindWidget))
  UTextBlock* HitPointsText;

  UPROPERTY(meta=(BindWidget))
  UProgressBar* HitPointsBar;

  UPROPERTY(meta=(BindWidget))
  UTextBlock* PowerText;

  UPROPERTY(meta=(BindWidget))
  UProgressBar* PowerBar;

  UPROPERTY(meta=(BindWidget))
  UTextBlock* SpeedText;

  UPROPERTY(meta=(BindWidget))
  UTextBlock* WeaponNameText;
  
  UPROPERTY()
  UTargetingWidget* TargetingWidget;

  UPROPERTY(meta=(BindWidget))
  UCanvasPanel* HUDPanel;

public:

  virtual void SetTargetingWidget(UTargetingWidget* NewTargetingWidget);

};
