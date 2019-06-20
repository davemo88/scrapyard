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

  typedef bool(*FBetterComparator)(int32, int32);
  void SetNewValue(int32 NewValue, int32 OldValue, FBetterComparator IsBetter);

protected:

  void NativeConstruct() override;

  UPROPERTY(meta=(BindWidget))
  UTextBlock* NewValueText;

  UPROPERTY(meta=(BindWidget))
  UImage* NewValueArrow;
	
};
