// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Blueprint/UserWidget.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotMovementComponent.h"
#include "RobotTunerWidget.generated.h"

USTRUCT()
struct FRobotTuneParams
{
  GENERATED_BODY()

  UPROPERTY()
  FString GroundFriction;

  UPROPERTY()
  FString BoostHoldThresholdTime;

  UPROPERTY()
  FString ControlType;
};

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotTunerWidget : public UUserWidget
{
  GENERATED_BODY()

public:

  void SetRobotChar(ARobotCharacter* NewRobotChar);

  ARobotCharacter* RobotChar;
  URobotMovementComponent* RobotMovementComp;
  
protected:

  void NativeConstruct();

  UPROPERTY(meta=(BindWidget))
  UEditableTextBox* GroundFrictionTextBox;
  UPROPERTY(meta=(BindWidget))
  UEditableTextBox* BoostHoldThresholdTimeTextBox;

  UPROPERTY(meta=(BindWidget))
  UButton* SetNewTuneButton;

  UPROPERTY(meta=(BindWidget))
  UComboBoxString* ControlTypeComboBox;

  UFUNCTION()
  void SetNewTune();

  FRobotTuneParams GetTuneParams();
  
};
