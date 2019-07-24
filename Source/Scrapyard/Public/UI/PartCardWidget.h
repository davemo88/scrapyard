// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/SizeBox.h"
#include "Components/ScaleBox.h"
#include "PartCardWidget.generated.h"

class URobotPart;
struct FStatText;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardClickedDelegate, UPartCardWidget*, Card);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardDoubleClickedDelegate, URobotPart*, Part);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardMouseEnteredDelegate, URobotPart*, Part);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardMouseLeftDelegate, URobotPart*, Part);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFadeOutFinishedDelegate, UPartCardWidget*, PartCardWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardDraggedDelegate, UPartCardWidget*, PartCardWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCardDroppedDelegate, UPartCardWidget*, PartCardWidget, UDragDropOperation*, DragDropOp);

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UPartCardWidget : public UUserWidget
{
  GENERATED_BODY()

public:

  void SetRobotPart(URobotPart* RobotPart);
  void SetRobotPart(TSubclassOf<URobotPart> RobotPartClass);

  UPROPERTY(BlueprintReadOnly)
  URobotPart* RobotPart;

  UPROPERTY(BlueprintReadOnly)
  TSubclassOf<URobotPart> RobotPartClass;

  FCardClickedDelegate CardClickedDelegate;
  FCardDoubleClickedDelegate CardDoubleClickedDelegate;
  FCardMouseEnteredDelegate CardMouseEnteredDelegate;
  FCardMouseEnteredDelegate CardMouseLeftDelegate;

//  UPROPERTY(meta=(BindWidget))
//  UScaleBox* CardScaleBox;
//
  UPROPERTY(meta=(BindWidget))
  USizeBox* CardSizeBox;

  bool bHoverBorderActive = false;

  bool bCanBeDragged = false;

  UUMGSequencePlayer* PlayFadeOut();

  FFadeOutFinishedDelegate FadeOutFinishedDelegate;
  FCardDraggedDelegate CardDraggedDelegate;
  FCardDroppedDelegate CardDroppedDelegate;

  void OnFadeOutFinished(UUMGSequencePlayer & SequencePlayer);

protected:

  FReply NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;
  FReply NativeOnMouseButtonUp(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;
  
  bool bMouseDownOnCard;

//  FReply NativeOnMouseMove(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent);

  void NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;

  void NativeOnMouseLeave(const FPointerEvent & InMouseEvent) override;

  FReply NativeOnMouseButtonDoubleClick(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;

  void NativeOnDragDetected(const FGeometry & InGeometry, const FPointerEvent & InDragDropEvent, UDragDropOperation *& OutOperation) override;

  bool NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation) override;

  void AddStatsText();

  void AddStatLine(FStatText StatText);

  UFUNCTION()
  void OnPartCardClicked();

  UPROPERTY(meta=(BindWidget))
  UBorder* CardBackground;

  UPROPERTY(meta=(BindWidget))
  UImage* PartTypeIcon;

  UPROPERTY(meta=(BindWidget))
  UVerticalBox* StatsBox;

  UPROPERTY(meta=(BindWidget))
  UBorder* HoverBorder;

  UPROPERTY(meta=(BindWidgetAnim))
  UWidgetAnimation* ShowHoverBorder;

  UPROPERTY(meta=(BindWidgetAnim))
  UWidgetAnimation* HideHoverBorder;

  UPROPERTY(meta=(BindWidgetAnim))
  UWidgetAnimation* DraftCard;

  UPROPERTY(meta=(BindWidgetAnim))
  UWidgetAnimation* FadeOut;

};
