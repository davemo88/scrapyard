// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YourPartsWidget.generated.h"

class UButton;
class UScrollBox;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UYourPartsWidget : public UUserWidget
{
  GENERATED_BODY()

protected:
  
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
  UButton* HandheldFilterButton;
  UPROPERTY(meta=(BindWidget))   
  UButton* ChipFilterButton;

  void EmptyDisplayedPartsBox();

  void PopulateDisplayedPartsBox(TArray<URobotPart*> RobotParts);

public:

  UPROPERTY(meta=(BindWidget))   
  UScrollBox* DisplayedPartsBox;
  
};
