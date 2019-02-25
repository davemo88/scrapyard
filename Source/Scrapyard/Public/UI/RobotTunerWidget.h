// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableTextBox.h"
#include "Blueprint/UserWidget.h"
#include "Robots/RobotCharacter.h"
#include "Robots/RobotMovementComponent.h"
#include "RobotTunerWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotTunerWidget : public UUserWidget
{
  GENERATED_BODY()

public:

  void SetRobotChar(ARobotCharacter* NewRobotChar);
  
protected:

  ARobotCharacter* RobotChar;
  URobotMovementComponent* RobotMovementComp;

  void NativeConstruct();

  UPROPERTY(meta=(BindWidget))
  UEditableTextBox* GroundFrictionTextBox;
  UPROPERTY(meta=(BindWidget))
  UEditableTextBox* BoostHoldThresholdTimeTextBox;

  void SetNewTune();

  UFUNCTION(Server, WithValidation, Reliable)
  void ServerSetNewTune();
  
};
