// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageWidget.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/HandheldPart.h"

void UGarageWidget::NativeConstruct()
{
  Super::NativeConstruct();

  InstalledHeadWidget->InstalledPartType = UHeadPart::StaticClass();
  InstalledCoreWidget->InstalledPartType = UCorePart::StaticClass();
  InstalledArmsWidget->InstalledPartType = UArmsPart::StaticClass();
  InstalledLegsWidget->InstalledPartType = ULegsPart::StaticClass();
  InstalledRightHandheldWidget->InstalledPartType = UHandheldPart::StaticClass();
}

void UGarageWidget::SetInstalledParts(UPartAssignment* PartAssignment)
{
  InstalledHeadWidget->SetInstalledPart(PartAssignment->GetHead());
  InstalledCoreWidget->SetInstalledPart(PartAssignment->GetCore());
  InstalledArmsWidget->SetInstalledPart(PartAssignment->GetArms());
  InstalledLegsWidget->SetInstalledPart(PartAssignment->GetLegs());
  InstalledRightHandheldWidget->SetInstalledPart(PartAssignment->GetRightHandheld());
}
