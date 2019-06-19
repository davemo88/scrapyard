// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/StatLineWidget.h"
#include "Components/Image.h"
#include "RobotStatLineWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API URobotStatLineWidget : public UStatLineWidget
{
  GENERATED_BODY()
	
public:

  virtual void SetStatLine(FStatText) override;

  void SetNewValue(FText NewStatValue, bool bBetter);

protected:

  UPROPERTY(meta=(BindWidget))
  UTextBlock* NewValue;

  UPROPERTY(meta=(BindWidget))
  UImage* NewValueArrow;
	
};
