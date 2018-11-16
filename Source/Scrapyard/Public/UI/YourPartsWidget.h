// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YourPartsWidget.generated.h"

class UButton;
class UScrollBox;
class UPartCardWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewPartCardAdded, UPartCardWidget*, PartCard);

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UYourPartsWidget : public UUserWidget
{
  GENERATED_BODY()

public:

  UPROPERTY()
  USoloDraft* CurrentDraft;

  void ClearDisplayedCards();

  void AddDisplayedCard(UPartCardWidget* Card);

  void AddDisplayedPart(URobotPart* RobotPart);

  void DisplayParts(TArray<URobotPart*> RobotParts);

  void DisplayAll();

  FNewPartCardAdded NewPartCardAdded;

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
  UScrollBox* DisplayedCards;

  void NativeConstruct() override;

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
  
};
