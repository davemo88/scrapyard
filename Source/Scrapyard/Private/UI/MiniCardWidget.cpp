// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCardWidget.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "UI/UIAssets.h"
#include "Parts/RobotPart.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/GameViewportClient.h"
#include "Components/CanvasPanelSlot.h"

void UMiniCardWidget::SetRobotPart(URobotPart* NewRobotPart)
{
  Super::SetRobotPart(NewRobotPart);
  if (RobotPart->Manufacturer->MiniCard)
  {
    CardBackground->SetBrushFromTexture(RobotPart->Manufacturer->MiniCard);
  }
  if (PartCardWidget != nullptr && RobotPart != nullptr)
  {
    PartCardWidget->SetRobotPart(RobotPart);
  }
}

void UMiniCardWidget::NativeConstruct()
{
  bShowPartCardOnMouseEnter = true;
  PartCardWidget = CreateWidget<UPartCardWidget>(GetOwningPlayer(), UScrapyardGameInstance::AssetsBP->UIAssetsBP->PartCardWidgetBP);
  if (RobotPart != nullptr)
  {
    PartCardWidget->SetRobotPart(RobotPart);
  }
}

void UMiniCardWidget::NativeOnMouseEnter(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnMouseEnter"), *GetName());
  if (bShowPartCardOnMouseEnter && !RobotPart->IsDefaultPart() && PartCardWidget != nullptr && GetWorld())
  {
    GetWorld()->GetTimerManager().SetTimer(HoverTimerHandle, this, &UMiniCardWidget::ShowPartCard, 0.3f, false);
  }
  Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UMiniCardWidget::NativeOnMouseLeave(const FPointerEvent & InMouseEvent)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnMouseLeave"), *GetName());
  Super::NativeOnMouseLeave(InMouseEvent);
  if (GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(HoverTimerHandle))
  {
    GetWorld()->GetTimerManager().ClearTimer(HoverTimerHandle);
//    HoverTimerHandle.Invalidate();
  }
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

void UMiniCardWidget::ShowPartCard()
{
  PartCardWidget->AddToViewport();
// https://answers.unrealengine.com/questions/110422/what-is-the-best-way-to-get-size-of-widget-in-view.html
// this will update the desired size of the part card widget since it's 0x0 until it actually ticks to render
  PartCardWidget->ForceLayoutPrepass();

  const FVector2D AbsoluteSize = GetCachedGeometry().GetAbsoluteSize();
  const FVector2D LocalSize = GetCachedGeometry().GetLocalSize();
  const float ScalingFactor = AbsoluteSize.X / LocalSize.X;
  const FVector2D PartCardSize = PartCardWidget->GetDesiredSize() * ScalingFactor;

  const FGeometry ViewportWidgetGeometry = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld());
  const FVector2D ViewportOriginAbsolutePosition = ViewportWidgetGeometry.GetAbsolutePosition();
  const FVector2D ViewportPosition = GetCachedGeometry().GetAbsolutePosition() - ViewportOriginAbsolutePosition;

  const float Padding = 10 * ScalingFactor;
  const float LeftAdjustedX = ViewportPosition.X - PartCardSize.X - Padding;
  const float RightAdjustedX = ViewportPosition.X + AbsoluteSize.X + Padding;
  const float AdjustedX = LeftAdjustedX > 0 ? LeftAdjustedX : RightAdjustedX;

  const FVector2D ViewSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());

  const float AdjustedY = ViewportPosition.Y + PartCardSize.Y > ViewSize.Y ? ViewportPosition.Y - PartCardSize.Y + AbsoluteSize.Y : ViewportPosition.Y;

//    UE_LOG(LogTemp, Warning, TEXT("ViewportOriginAbsolutePosition %s"), *ViewportOriginAbsolutePosition.ToString());
//    UE_LOG(LogTemp, Warning, TEXT("Viewport Size %s"), *ViewSize.ToString());
//    UE_LOG(LogTemp, Warning, TEXT("ScalingFactor %f"), ScalingFactor);
//    UE_LOG(LogTemp, Warning, TEXT("PartCard Size %s"), *PartCardSize.ToString());
//    UE_LOG(LogTemp, Warning, TEXT("Adjusted X coordinate %f"), AdjustedX);
//    UE_LOG(LogTemp, Warning, TEXT("ViewportPosition %s"), *ViewportPosition.ToString());

  PartCardWidget->SetPositionInViewport(FVector2D(AdjustedX, AdjustedY));
  PartCardWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}
