// Fill out your copyright notice in the Description page of Project Settings.


#include "InstalledPartWidget.h"
#include "Parts/RobotPart.h"

void UInstalledPartWidget::NativeConstruct()
{
  UninstallButton->OnClicked.AddDynamic(this, &UInstalledPartWidget::OnUninstallButtonClicked);
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


