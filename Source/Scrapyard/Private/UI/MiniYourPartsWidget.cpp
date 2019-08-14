// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniYourPartsWidget.h"
#include "Scrapyard.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "UI/UIAssets.h"
#include "UI/CardWidgetBase.h"
#include "UI/MiniCardWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/GameViewportClient.h"

void UMiniYourPartsWidget::NativeConstruct()
{
  UE_LOG(LogUI, Verbose, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();
//  NewCardAddedDelegate.AddDynamic(this, &UMiniYourPartsWidget::OnNewCardAdded);
}

//void UMiniYourPartsWidget::OnNewCardAdded(UCardWidgetBase* Card)
//{
//  UE_LOG(LogUI, Verbose, TEXT("%s::OnNewCardAdded"), *GetName());
//  if (UMiniCardWidget* MiniCard = Cast<UMiniCardWidget>(Card))
//  {
//    MiniCard->CardMouseEnteredDelegate.AddDynamic(this, &UMiniYourPartsWidget::OnCardMouseEntered);
//  }
//}

//void UMiniYourPartsWidget::OnCardMouseEntered(UCardWidgetBase* Card)
//{
//  if (UMiniCardWidget* MiniCard = Cast<UMiniCardWidget>(Card))
//  {
//    if (GetWorld() && MiniCard->PartCardWidget && MiniCard->PartCardWidget->IsInViewport())
//    {
//      const UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//      const FVector2D ViewSize = ViewportClient->Viewport->GetSizeXY();
//      const FVector2D YourPartsSize = GetCachedGeometry().GetAbsoluteSize();
//      const FVector2D LocalYourPartsSize = GetCachedGeometry().GetLocalSize();
//      const float ApparentScalingFactor = YourPartsSize.X / LocalYourPartsSize.X;
//// https://answers.unrealengine.com/questions/110422/what-is-the-best-way-to-get-size-of-widget-in-view.html
//// this will update the desired size of the part card widget since it's 0x0 until it actually ticks to render
//      MiniCard->PartCardWidget->ForceLayoutPrepass();
//      const FVector2D PartCardSize = MiniCard->PartCardWidget->GetDesiredSize() * ApparentScalingFactor;
//      const float Padding = 10 * ApparentScalingFactor;
//      const float AdjustedX = ViewSize.X - YourPartsSize.X - PartCardSize.X - Padding;
//
//      const FVector2D ViewportOriginAbsolute = GetParent()->GetCachedGeometry().LocalToAbsolute(FVector2D(0,0));
//      const FVector2D MiniCardPosition = MiniCard->GetCachedGeometry().GetAbsolutePosition() - ViewportOriginAbsolute;
//      const FVector2D MiniCardSize = MiniCard->GetCachedGeometry().GetAbsoluteSize();
//
//      const float AdjustedY = MiniCardPosition.Y + PartCardSize.Y > ViewSize.Y ? MiniCardPosition.Y - PartCardSize.Y + MiniCardSize.Y : MiniCardPosition.Y;
//
////      UE_LOG(LogTemp, Warning, TEXT("Viewport Size %s"), *ViewSize.ToString());
////      UE_LOG(LogTemp, Warning, TEXT("YourParts Size %s"), *YourPartsSize.ToString());
////      UE_LOG(LogTemp, Warning, TEXT("ApparentScalingFactor %f"), ApparentScalingFactor);
////      UE_LOG(LogTemp, Warning, TEXT("PartCard Size %s"), *PartCardSize.ToString());
////      UE_LOG(LogTemp, Warning, TEXT("Adjusted X coordinate %f"), AdjustedX);
////      UE_LOG(LogTemp, Warning, TEXT("OriginAbsolute %s"), *ViewportOriginAbsolute.ToString());
////      UE_LOG(LogTemp, Warning, TEXT("MiniCardPosition %s"), *MiniCardPosition.ToString());
////      MiniCard->PartCardWidget->SetPositionInViewport(FVector2D(AdjustedX, AdjustedY));
//    }
//  }
//}

UCardWidgetBase* UMiniYourPartsWidget::GetCardWidget()
{
  return CreateWidget<UMiniCardWidget>(GetOwningPlayer(), UScrapyardGameInstance::GameInstance->AssetsBP->UIAssetsBP->MiniCardWidgetBP); 
}
