// Fill out your copyright notice in the Description page of Project Settings.


#include "InstalledPartWidget.h"
#include "Scrapyard.h"
#include "UI/PartCardWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Parts/RobotPart.h"

void UInstalledPartWidget::NativeConstruct()
{
  UninstallButton->OnClicked.AddDynamic(this, &UInstalledPartWidget::OnUninstallButtonClicked);
}

bool UInstalledPartWidget::NativeOnDrop(const FGeometry & InGeometry, const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation)
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeOnDrop"), *GetName());
  if (UPartCardWidget* PartCard = Cast<UPartCardWidget>(InOperation->DefaultDragVisual))
  {
    UE_LOG(LogUI, Log, TEXT("Part Card Dropped: %s"), *PartCard->RobotPart->PartName.ToString());
    UE_LOG(LogUI, Log, TEXT("Checking if it's a %s"), *InstalledPartType->GetName());
    if (PartCard->RobotPart->IsA(InstalledPartType))
    {
      UE_LOG(LogUI, Log, TEXT("Yay! it's a %s"), *InstalledPartType->GetName());
      CompatibleCardDroppedDelegate.Broadcast(PartCard);
    }
  }
  return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInstalledPartWidget::OnUninstallButtonClicked()
{
  PartUninstalledDelegate.Broadcast(InstalledPart);
// NOTE:
// handle actual uninstallation elsewhere?
// InstalledPart = nullptr;
//
}

void UInstalledPartWidget::SetInstalledPart(URobotPart* NewInstalledPart)
{
  InstalledPart = NewInstalledPart;
  PartName->SetText(InstalledPart->PartName);
}


