// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniYourPartsWidget.h"
#include "Scrapyard.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "UI/UIAssets.h"
#include "UI/CardWidgetBase.h"
#include "UI/MiniCardWidget.h"

void UMiniYourPartsWidget::NativeConstruct()
{
  UE_LOG(LogUI, Verbose, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();
  NewCardAddedDelegate.AddDynamic(this, &UMiniYourPartsWidget::OnNewCardAdded);
}

void UMiniYourPartsWidget::OnNewCardAdded(UCardWidgetBase* Card)
{
  UE_LOG(LogUI, Verbose, TEXT("%s::OnNewCardAdded"), *GetName());
  if (UMiniCardWidget* MiniCard = Cast<UMiniCardWidget>(Card))
  {
    MiniCard->CardMouseEnteredDelegate.AddDynamic(this, &UMiniYourPartsWidget::OnCardMouseEntered);
  }
}

void UMiniYourPartsWidget::OnCardMouseEntered(UCardWidgetBase* Card)
{
  if (UMiniCardWidget* MiniCard = Cast<UMiniCardWidget>(Card))
  {
    if (MiniCard->PartCardWidget && MiniCard->PartCardWidget->IsInViewport())
    {
      float MouseX;
      float MouseY;
      GetOwningPlayer()->GetMousePosition(MouseX, MouseY);
      UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this); 
      FVector2D YourPartsPosition = CanvasSlot->GetPosition();
      UE_LOG(LogTemp, Warning, TEXT("YourPartsPosition x coordinate %f"), YourPartsPosition.X);
      MiniCard->PartCardWidget->SetPositionInViewport(FVector2D(YourPartsPosition.X, MouseY));
    }
  }
}

UCardWidgetBase* UMiniYourPartsWidget::GetCardWidget()
{
  return CreateWidget<UMiniCardWidget>(GetOwningPlayer(), UScrapyardGameInstance::GameInstance->AssetsBP->UIAssetsBP->MiniCardWidgetBP); 
}
