// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/YourPartsWidget.h"
#include "FancyYourPartsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UFancyYourPartsWidget : public UYourPartsWidget
{
  GENERATED_BODY()
  
protected:

  virtual void NativeConstruct() override;
  
  UPROPERTY(meta=(BindWidget))   
  UButton* AllFilterButton;
  UPROPERTY(meta=(BindWidget))   
  UButton* HeadFilterButton;
  UPROPERTY(meta=(BindWidget))   
  UButton* CoreFilterButton;
  UPROPERTY(meta=(BindWidget))   
  UButton* ArmsFilterButton;
  UPROPERTY(meta=(BindWidget))   
  UButton* LegsFilterButton;
  UPROPERTY(meta=(BindWidget))   
  UButton* BoosterFilterButton;
  UPROPERTY(meta=(BindWidget))   
  UButton* HandheldFilterButton;
  UPROPERTY(meta=(BindWidget))   
  UButton* ChipFilterButton;
  UPROPERTY(meta=(BindWidget))
  UButton* DefaultPartsFilterButton;

  UFUNCTION()
  void OnAllFilterButtonClicked();
  UFUNCTION()
  void OnHeadFilterButtonClicked();
  UFUNCTION()
  void OnCoreFilterButtonClicked();
  UFUNCTION()
  void OnArmsFilterButtonClicked();
  UFUNCTION()
  void OnLegsFilterButtonClicked();
  UFUNCTION()
  void OnBoosterFilterButtonClicked();
  UFUNCTION()
  void OnHandheldFilterButtonClicked();
  UFUNCTION()
  void OnChipFilterButtonClicked();
  UFUNCTION()
  void OnDefaultPartsFilterButtonClicked();

  bool bDisplayDefaultParts;
  
};
