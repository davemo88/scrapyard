// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoloDraft.h"
#include "Parts/RobotPart.h"
#include "UI/CardWidgetBase.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "YourPartsWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewCardAdded, UCardWidgetBase*, NewCard);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardDroppedInYourPartsDelegate, UCardWidgetBase*, DroppedCard);

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

  UFUNCTION()
  void RemoveDisplayedCard(UCardWidgetBase* Card);

  UFUNCTION()
  void AddDisplayedPart(URobotPart* RobotPart);

  void DisplayParts(TArray<URobotPart*> RobotParts);

  void DisplayAll();

  FNewCardAdded NewCardAdded;
  FCardDroppedInYourPartsDelegate CardDroppedInYourPartsDelegate;

protected:

  UPROPERTY(meta=(BindWidget))   
  UScrollBox* DisplayedCards;

  UFUNCTION()
  void ReorderCards(UCardWidgetBase* DroppedOnCard, UDragDropOperation* DragDropOp);

  virtual void NativeConstruct() override;

  virtual bool NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation) override;

  UFUNCTION()
  void OnSortButtonClicked();
  void SortByUserOrder();
  void SortByType();
  void SortByColor();
  
};
