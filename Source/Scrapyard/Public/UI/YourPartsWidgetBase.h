// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"
#include "Scrapyard.h"
#include "Drafting/DraftBase.h"
#include "Parts/RobotPart.h"
#include "UI/CardWidgetBase.h"
#include "UI/PartCardDragDropOperation.h"
#include "YourPartsWidgetBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewCardAddedDelegate, UCardWidgetBase*, NewCard);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardDroppedInYourPartsDelegate, UCardWidgetBase*, DroppedCard);
/**
 * 
 */
UCLASS()
class SCRAPYARD_API UYourPartsWidgetBase : public UUserWidget
{
  GENERATED_BODY()

public:

  void SetCurrentDraft(UDraftBase* NewDraft);

  UFUNCTION()
  void DisplayPart(URobotPart* RobotPart);

  UFUNCTION()
  void DisplayParts(TArray<URobotPart*> NewDisplayedParts);

  UFUNCTION()
  virtual void RemoveDisplayedCard(UCardWidgetBase* Card);

  FNewCardAddedDelegate NewCardAddedDelegate;
  FCardDroppedInYourPartsDelegate CardDroppedInYourPartsDelegate;

  virtual bool NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation) override;

  void DisplayUnassignedParts();

protected:

  UPROPERTY()
  UDraftBase* CurrentDraft;

  UPROPERTY(meta=(BindWidget))   
  UPanelWidget* CardDisplayPanel;

  UPROPERTY()
  TArray<URobotPart*> DisplayedParts;

  void SortDisplayedParts();

  void RefreshDisplayedCards();

  virtual UCardWidgetBase* GetCardWidget();

};
