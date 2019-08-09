// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/YourPartsWidgetBase.h"
#include "MiniYourPartsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UMiniYourPartsWidget : public UYourPartsWidgetBase
{
  GENERATED_BODY()

public:

  virtual UCardWidgetBase* GetCardWidget() override;
  
};
