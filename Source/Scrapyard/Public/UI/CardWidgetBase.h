// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "CardWidgetBase.generated.h"

class URobotPart;
struct FStatText;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardClickedDelegate, UCardWidgetBase*, Card);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardDoubleClickedDelegate, URobotPart*, Part);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardMouseEnteredDelegate, URobotPart*, Part);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardMouseLeftDelegate, URobotPart*, Part);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFadeOutFinishedDelegate, UPartCardWidget*, PartCardWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardDraggedDelegate, UCardWidgetBase*, CardWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCardDroppedDelegate, UCardWidgetBase*, CardWidget, UDragDropOperation*, DragDropOp);

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UCardWidgetBase : public UUserWidget
{
  GENERATED_BODY()

public:
  
  virtual void SetRobotPart(URobotPart* RobotPart);

  UPROPERTY(BlueprintReadOnly)
  URobotPart* RobotPart;

  FCardClickedDelegate CardClickedDelegate;
  FCardDoubleClickedDelegate CardDoubleClickedDelegate;
  FCardMouseEnteredDelegate CardMouseEnteredDelegate;
  FCardMouseEnteredDelegate CardMouseLeftDelegate;

  bool bHoverBorderActive = false;

  bool bCanBeDragged = false;

  FCardDraggedDelegate CardDraggedDelegate;
  FCardDroppedDelegate CardDroppedDelegate;

protected:

  virtual FReply NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;
  FReply NativeOnMouseButtonUp(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;

  virtual void NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;

  virtual void NativeOnMouseLeave(const FPointerEvent & InMouseEvent) override;

  virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override;

//  void NativeOnDragDetected(const FGeometry & InGeometry, const FPointerEvent & InDragDropEvent, UDragDropOperation *& OutOperation) override;
//
//  bool NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation) override;

  UPROPERTY(meta=(BindWidget))
  UBorder* CardBackground;
  
  UPROPERTY(meta=(BindWidget))
  UTextBlock* CardTitle;

  UPROPERTY(meta=(BindWidget))
  UImage* PartTypeIcon;

  UPROPERTY(meta=(BindWidget))
  UBorder* HoverBorder;

  UPROPERTY(meta=(BindWidgetAnim))
  UWidgetAnimation* ShowHoverBorder;

  UPROPERTY(meta=(BindWidgetAnim))
  UWidgetAnimation* HideHoverBorder;

};
