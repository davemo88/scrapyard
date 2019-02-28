// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Parts/RobotPart.h"
#include "StatLineWidget.generated.h"

class UTextBlock;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class SCRAPYARD_API UStatLineWidget : public UUserWidget
{
  GENERATED_BODY()

public:
  
  UFUNCTION()
  void SetStatLine(FStatText StatText);

protected:

  UPROPERTY(meta=(BindWidget))
  UTextBlock* StatName;
  UPROPERTY(meta=(BindWidget))
  UTextBlock* StatValue;

};
