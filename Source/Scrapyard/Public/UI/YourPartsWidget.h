// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoloDraft.h"
#include "Parts/RobotPart.h"
#include "UI/PartCardWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "YourPartsWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewPartCardAdded, UPartCardWidget*, PartCard);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPartCardDroppedDelegate, UPartCardWidget*, DroppedCard);

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
  FPartCardDroppedDelegate PartCardDroppedDelegate;

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

  bool NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation);

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
  void OnHandheldFilterButtonClicked();
  
};
