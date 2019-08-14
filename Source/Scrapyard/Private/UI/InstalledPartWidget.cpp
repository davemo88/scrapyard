// Fill out your copyright notice in the Description page of Project Settings.


#include "InstalledPartWidget.h"
#include "Scrapyard.h"
#include "UI/CardWidgetBase.h"
#include "Blueprint/DragDropOperation.h"
#include "Parts/RobotPart.h"

void UInstalledPartWidget::NativeConstruct()
{
  UninstallButton->OnClicked.AddDynamic(this, &UInstalledPartWidget::OnUninstallButtonClicked);
}

bool UInstalledPartWidget::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnDrop"), *GetName());
  if (UCardWidgetBase* Card = Cast<UCardWidgetBase>(InOperation->DefaultDragVisual))
  {
    UE_LOG(LogUI, Log, TEXT("Part Card Dropped: %s"), *Card->RobotPart->PartName.ToString());
    UE_LOG(LogUI, Log, TEXT("Checking if it's a %s"), *InstalledPartType->GetName());
    if (Card->RobotPart->IsA(InstalledPartType))
    {
      UE_LOG(LogUI, Log, TEXT("Yay! it's a %s"), *InstalledPartType->GetName());
      CompatibleCardDroppedDelegate.Broadcast(Card);
    }
  }
  return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInstalledPartWidget::OnUninstallButtonClicked()
{
  UninstallButtonClickedDelegate.Broadcast();
}

void UInstalledPartWidget::SetInstalledPart(URobotPart* NewInstalledPart)
{
  if (InstalledPart != nullptr)
  {
    UE_LOG(LogUI, Log, TEXT("%s::SetInstalledPart - broadcasting uninstalled part"), *GetName());
    PartUninstalledDelegate.Broadcast(InstalledPart);
  }
  InstalledPart = NewInstalledPart;
  if (InstalledPart != nullptr)
  {
    MiniCard->SetRobotPart(InstalledPart);
  }
}

void UInstalledPartWidget::SetInstalledPartType(TSubclassOf<URobotPart> NewInstalledPartType)
{
  InstalledPartType = NewInstalledPartType;
  URobotPart* Part = NewObject<URobotPart>(this, NewInstalledPartType);
//  PartTypeIcon->SetBrushFromTexture(Part->GetPartTypeIcon());
}

//void UInstalledPartWidget::SetDefaultPart(URobotPart* NewDefaultPart)
//{
//  if (NewDefaultPart->IsA(InstalledPartType))
//  {
//    DefaultPart = NewDefaultPart;
//  }
//}
//

//void UInstalledPartWidget::OnCardMouseEntered(UCardWidgetBase* Card)
//{
//// https://answers.unrealengine.com/questions/110422/what-is-the-best-way-to-get-size-of-widget-in-view.html
//// this will update the desired size of the part card widget since it's 0x0 until it actually ticks to render
//    PartCardWidget->ForceLayoutPrepass();
//    if (UCanvasPanelSlot* PartCardSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(PartCardWidget))
//    {
//      if (PartCardSlot->Parent != nullptr)
//      {
//        const FVector2D ViewportOriginAbsolute = PartCardSlot->Parent->GetCachedGeometry().LocalToAbsolute(FVector2D(0,0));
//        UE_LOG(LogTemp, Warning, TEXT("OriginAbsolute %s"), *ViewportOriginAbsolute.ToString());
//      }
//    }
//
//    const FVector2D AbsoluteSize = GetCachedGeometry().GetAbsoluteSize();
//    const FVector2D LocalSize = GetCachedGeometry().GetLocalSize();
//    const float ScalingFactor = AbsoluteSize.X / LocalSize.X;
//    const FVector2D PartCardSize = PartCardWidget->GetDesiredSize() * ScalingFactor;
//
//    const UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//    const FVector2D ViewSize = ViewportClient->Viewport->GetSizeXY();
//
//    const FVector2D ViewportPosition = GetCachedGeometry().GetAbsolutePosition();// - ViewportOriginAbsolute;
//
//    const float Padding = 10 * ScalingFactor;
//    const float LeftAdjustedX = ViewportPosition.X - PartCardSize.X - Padding;
//    const float RightAdjustedX = ViewportPosition.X + AbsoluteSize.X + Padding;
//    const float AdjustedX = LeftAdjustedX > 0 ? LeftAdjustedX : RightAdjustedX;
//
//    const float AdjustedY = ViewportPosition.Y + PartCardSize.Y > ViewSize.Y ? ViewportPosition.Y - PartCardSize.Y : ViewportPosition.Y;
//
//    UE_LOG(LogTemp, Warning, TEXT("Viewport Size %s"), *ViewSize.ToString());
//    UE_LOG(LogTemp, Warning, TEXT("ScalingFactor %f"), ScalingFactor);
//    UE_LOG(LogTemp, Warning, TEXT("PartCard Size %s"), *PartCardSize.ToString());
//    UE_LOG(LogTemp, Warning, TEXT("Adjusted X coordinate %f"), AdjustedX);
//    UE_LOG(LogTemp, Warning, TEXT("ViewportPosition %s"), *ViewportPosition.ToString());
//    PartCardWidget->SetPositionInViewport(FVector2D(AdjustedX, AdjustedY));
//}
