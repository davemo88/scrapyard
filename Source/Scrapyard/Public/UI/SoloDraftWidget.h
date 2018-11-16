// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoloDraftWidget.generated.h"

class UUserWidget;
class UYourPartsWidget;
class UUniformGridPanel;
class UHorizontalBox;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API USoloDraftWidget : public UUserWidget
{
  GENERATED_BODY()

protected:

  void NativeConstruct() override;

public:

//TODO: clean up interface to this widget
  UPROPERTY(meta=(BindWidget))
  UUniformGridPanel* PackDisplayPanel;

  UPROPERTY(meta=(BindWidget))
  UYourPartsWidget* YourPartsWidget;

  UPROPERTY(meta=(BindWidget))
  UTextBlock* PickCounter;

  UFUNCTION()
  void UpdatePickCounter();

  void DisplayNextPack();
  
};
