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
