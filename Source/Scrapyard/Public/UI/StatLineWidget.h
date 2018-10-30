// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatLineWidget.generated.h"

class UHorizontalBox;
/**
 * 
 */
UCLASS()
class SCRAPYARD_API UStatLineWidget : public UUserWidget
{
  GENERATED_BODY()

protected:

  UPROPERTY(meta=(BindWidget))
  UTextBlock* StatName;
  UPROPERTY(meta=(BindWidget))
  UTextBlock* StatValue;

public:
  
  UFUNCTION()
  void SetStatLine(FStatText StatText);

  UFUNCTION()
  void SetStatValue(FText NewStatValue);
  
};
