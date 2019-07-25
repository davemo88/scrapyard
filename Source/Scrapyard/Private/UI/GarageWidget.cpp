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

  InstalledHeadWidget->SetInstalledPartType(UHeadPart::StaticClass());
  InstalledCoreWidget->SetInstalledPartType(UCorePart::StaticClass());
  InstalledArmsWidget->SetInstalledPartType(UArmsPart::StaticClass());
  InstalledLegsWidget->SetInstalledPartType(ULegsPart::StaticClass());
  InstalledRightHandheldWidget->SetInstalledPartType(UHandheldPart::StaticClass());
}

void UGarageWidget::SetInstalledParts(UPartAssignment* PartAssignment)
{
  InstalledHeadWidget->SetInstalledPart(PartAssignment->GetHead());
  InstalledCoreWidget->SetInstalledPart(PartAssignment->GetCore());
  InstalledArmsWidget->SetInstalledPart(PartAssignment->GetArms());
  InstalledLegsWidget->SetInstalledPart(PartAssignment->GetLegs());
  InstalledRightHandheldWidget->SetInstalledPart(PartAssignment->GetRightHandheld());
}
