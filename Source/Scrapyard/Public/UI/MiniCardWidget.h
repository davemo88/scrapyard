// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scrapyard.h"
#include "UI/CardWidgetBase.h"
#include "UI/PartCardWidget.h"
#include "MiniCardWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UMiniCardWidget : public UCardWidgetBase
{
  GENERATED_BODY()
  
public:

  virtual void SetRobotPart(URobotPart* RobotPart) override;

  bool bShowPartCardOnMouseEnter;

  UPROPERTY()
  UPartCardWidget* PartCardWidget;

  void RemoveFromParent() override;
  
  FTimerHandle HoverTimerHandle;

protected:

  virtual void NativeConstruct() override;

  virtual void NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;

  virtual void NativeOnMouseLeave(const FPointerEvent & InMouseEvent) override;

  UFUNCTION()
  virtual void ShowPartCard();
  
};
