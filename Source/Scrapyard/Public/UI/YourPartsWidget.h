// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/YourPartsWidgetBase.h"
#include "Components/ScrollBox.h"
#include "YourPartsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UYourPartsWidget : public UYourPartsWidgetBase
{
  GENERATED_BODY()

public:

  virtual void AddDisplayedPart(URobotPart* RobotPart) override;

protected:

  UFUNCTION()
  void ReorderCards(UCardWidgetBase* DroppedOnCard, UDragDropOperation* DragDropOp);

  UFUNCTION()
  void OnSortButtonClicked();

  void SortByType();
  
};
