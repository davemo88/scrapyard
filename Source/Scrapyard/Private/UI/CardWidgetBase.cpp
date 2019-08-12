// Fill out your copyright notice in the Description page of Project Settings.


#include "CardWidgetBase.h"
#include "Scrapyard.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Parts/RobotPart.h"

void UCardWidgetBase::SetRobotPart(URobotPart* NewRobotPart)
{
  RobotPart = NewRobotPart;
  CardTitle->SetText(RobotPart->PartName); 
  if (UTexture2D* CardIcon = RobotPart->GetPartTypeIcon())
  {
    PartTypeIcon->SetBrushFromTexture(CardIcon); 
  }
}

FReply UCardWidgetBase::NativeOnMouseButtonDoubleClick(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnMouseButtonDoubleClick"), *GetName());
  CardDoubleClickedDelegate.Broadcast(RobotPart);
  return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}

void UCardWidgetBase::NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Verbose, TEXT("%s::NativeOnMouseEnter"), *GetName());
  CardMouseEnteredDelegate.Broadcast(this);
  if (bHoverBorderActive)
  {
    PlayAnimation(ShowHoverBorder);
  }
  Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UCardWidgetBase::NativeOnMouseLeave(const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Verbose, TEXT("%s::NativeOnMouseLeave"), *GetName());
  CardMouseLeftDelegate.Broadcast(this);
  if (bHoverBorderActive)
  {
    PlayAnimation(HideHoverBorder);
  }
  Super::NativeOnMouseLeave(InMouseEvent);
}

FReply UCardWidgetBase::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnMouseButtonDown"), *GetName());
// stops OnMouseLeave event from firing by not calling Super
//  UDragDropOperation* DragDropOp = UWidgetBlueprintLibrary::CreateDragDropOperation(UPartCardDragDropOperation::StaticClass());
//
  if (bCanBeDragged)
  {
    return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
  }

  return FReply::Handled();
//  return FReply::Handled().BeginDragDrop(MakeShareable(new FDragDropOperation()));
//  return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UCardWidgetBase::NativeOnMouseButtonUp(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnMouseButtonUp"), *GetName());
// stops OnMouseEnter event from firing by not calling Super
  CardClickedDelegate.Broadcast(this);
//  return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
  return FReply::Handled();
}

//void UCardWidgetBase::NativeOnDragDetected(const FGeometry & InGeometry, const FPointerEvent & InDragDropEvent, UDragDropOperation *& OutOperation)
//{
//  UE_LOG(LogUI, Log, TEXT("%s::NativeOnDragDetected"), *GetName());
//  Super::NativeOnDragDetected(InGeometry, InDragDropEvent, OutOperation);
//  OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UPartCardDragDropOperation::StaticClass());
//  OutOperation->DefaultDragVisual = this;
//  CardDraggedDelegate.Broadcast(this);
//}
//
//bool UCardWidgetBase::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
//{
//  UE_LOG(LogUI, Log, TEXT("%s::NativeOnDrop"), *GetName());
//  CardDroppedDelegate.Broadcast(this,InOperation);
//  return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
//}




