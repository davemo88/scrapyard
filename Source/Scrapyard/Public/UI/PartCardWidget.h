// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CardWidgetBase.h"
#include "Components/VerticalBox.h"
#include "Components/SizeBox.h"
#include "Components/ScaleBox.h"
#include "PartCardWidget.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardClickedDelegate, UPartCardWidget*, Card);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardDoubleClickedDelegate, URobotPart*, Part);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardMouseEnteredDelegate, URobotPart*, Part);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardMouseLeftDelegate, URobotPart*, Part);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFadeOutFinishedDelegate, UPartCardWidget*, PartCardWidget);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardDraggedDelegate, UPartCardWidget*, PartCardWidget);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCardDroppedDelegate, UPartCardWidget*, PartCardWidget, UDragDropOperation*, DragDropOp);

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UPartCardWidget : public UCardWidgetBase
{
  GENERATED_BODY()

public:

  virtual void SetRobotPart(URobotPart* RobotPart) override;
//
//  UPROPERTY(BlueprintReadOnly)
//  URobotPart* RobotPart;
//
//  FCardClickedDelegate CardClickedDelegate;
//  FCardDoubleClickedDelegate CardDoubleClickedDelegate;
//  FCardMouseEnteredDelegate CardMouseEnteredDelegate;
//  FCardMouseEnteredDelegate CardMouseLeftDelegate;

//  UPROPERTY(meta=(BindWidget))
//  UScaleBox* CardScaleBox;
//
  UPROPERTY(meta=(BindWidget))
  USizeBox* CardSizeBox;

//  bool bHoverBorderActive = false;
//
//  bool bCanBeDragged = false;
//
//  FCardDraggedDelegate CardDraggedDelegate;
//  FCardDroppedDelegate CardDroppedDelegate;

  UUMGSequencePlayer* PlayFadeOut();

  FFadeOutFinishedDelegate FadeOutFinishedDelegate;

  void OnFadeOutFinished(UUMGSequencePlayer & SequencePlayer);

protected:

//  FReply NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;
//  FReply NativeOnMouseButtonUp(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;
//  
//  bool bMouseDownOnCard;
//
////  FReply NativeOnMouseMove(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent);
//
//  void NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;
//
//  void NativeOnMouseLeave(const FPointerEvent & InMouseEvent) override;
//
//  FReply NativeOnMouseButtonDoubleClick(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;
//
  void NativeOnDragDetected(const FGeometry & InGeometry, const FPointerEvent & InDragDropEvent, UDragDropOperation *& OutOperation) override;

  bool NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation) override;

  void AddStatsText();

  void AddStatLine(FStatText StatText);

//  UPROPERTY(meta=(BindWidget))
//  UBorder* CardBackground;
//
//  UPROPERTY(meta=(BindWidget))
//  UImage* PartTypeIcon;
//
  UPROPERTY(meta=(BindWidget))
  UVerticalBox* StatsBox;

//  UPROPERTY(meta=(BindWidget))
//  UBorder* HoverBorder;
//
//  UPROPERTY(meta=(BindWidgetAnim))
//  UWidgetAnimation* ShowHoverBorder;
//
//  UPROPERTY(meta=(BindWidgetAnim))
//  UWidgetAnimation* HideHoverBorder;

  UPROPERTY(meta=(BindWidgetAnim))
  UWidgetAnimation* DraftCard;

  UPROPERTY(meta=(BindWidgetAnim))
  UWidgetAnimation* FadeOut;

};
