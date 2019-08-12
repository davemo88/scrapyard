// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCardWidget.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "UI/UIAssets.h"
#include "Parts/RobotPart.h"

void UMiniCardWidget::SetRobotPart(URobotPart* NewRobotPart)
{
  Super::SetRobotPart(NewRobotPart);
  if (RobotPart->Manufacturer->MiniCard)
  {
    CardBackground->SetBrushFromTexture(RobotPart->Manufacturer->MiniCard);
  }
}

void UMiniCardWidget::NativeConstruct()
{
  PartCardWidget = CreateWidget<UPartCardWidget>(GetOwningPlayer(), UScrapyardGameInstance::AssetsBP->UIAssetsBP->PartCardWidgetBP);
  if (RobotPart != nullptr)
  {
    PartCardWidget->SetRobotPart(RobotPart);
  }
}

void UMiniCardWidget::NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnMouseEnter"), *GetName());
  if (bShowPartCardOnMouseEnter && PartCardWidget != nullptr)
  {
    PartCardWidget->AddToViewport();
    float MouseX;
    float MouseY;
    GetOwningPlayer()->GetMousePosition(MouseX, MouseY);
    PartCardWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
    PartCardWidget->SetPositionInViewport(FVector2D(MouseX, MouseY));
  }
  Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UMiniCardWidget::NativeOnMouseLeave(const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnMouseLeave"), *GetName());
  Super::NativeOnMouseLeave(InMouseEvent);
  if (PartCardWidget != nullptr && PartCardWidget->IsInViewport())
  {
    PartCardWidget->RemoveFromViewport();
  }
}

void UMiniCardWidget::RemoveFromParent()
{
  if (PartCardWidget != nullptr && PartCardWidget->IsInViewport())
  {
    PartCardWidget->RemoveFromViewport();
  }
  Super::RemoveFromParent();
}
