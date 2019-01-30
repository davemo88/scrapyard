// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MatchTimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UMatchTimerWidget : public UUserWidget
{
  GENERATED_BODY()
  
  UPROPERTY(meta=(BindWidget))
  UTextBlock* MatchTime;

public:

  UFUNCTION()
  void StartMatchTimer();
  UFUNCTION()
  void StopMatchTimer();
  UFUNCTION()
  void UpdateMatchTimer();
  
};
