// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageWidget.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/HandheldPart.h"
#include "UI/YourPartsWidget.h"

void UGarageWidget::NativeConstruct()
{
  Super::NativeConstruct();

  InstalledHeadWidget->SetInstalledPartType(UHeadPart::StaticClass());
  InstalledCoreWidget->SetInstalledPartType(UCorePart::StaticClass());
  InstalledArmsWidget->SetInstalledPartType(UArmsPart::StaticClass());
  InstalledLegsWidget->SetInstalledPartType(ULegsPart::StaticClass());
  InstalledRightHandheldWidget->SetInstalledPartType(UHandheldPart::StaticClass());

  NewValueAssignment = NewObject<UPartAssignment>();
  NewValueStats = NewObject<URobotStats>();
}

void UGarageWidget::SetSoloDraft(USoloDraft* NewSoloDraft)
{
  SoloDraft = NewSoloDraft;
  YourPartsWidget->SoloDraft = SoloDraft;

  if (SoloDraft != nullptr)
  {
    InstalledHeadWidget->SetInstalledPart(SoloDraft->PartAssignment->GetHead());
    InstalledCoreWidget->SetInstalledPart(SoloDraft->PartAssignment->GetCore());
    InstalledArmsWidget->SetInstalledPart(SoloDraft->PartAssignment->GetArms());
    InstalledLegsWidget->SetInstalledPart(SoloDraft->PartAssignment->GetLegs());
    InstalledRightHandheldWidget->SetInstalledPart(SoloDraft->PartAssignment->GetRightHandheld());

    SoloDraft->PartAssignment->HeadAssignmentChangedDelegate.AddDynamic(GarageWidget->InstalledHeadWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->CoreAssignmentChangedDelegate.AddDynamic(GarageWidget->InstalledCoreWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->ArmsAssignmentChangedDelegate.AddDynamic(GarageWidget->InstalledArmsWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->LegsAssignmentChangedDelegate.AddDynamic(GarageWidget->InstalledLegsWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->RightHandheldAssignmentChangedDelegate.AddDynamic(GarageWidget->InstalledRightHandheldWidget, &UInstalledPartWidget::SetInstalledPart);
  }

  NewValueAssignment->SetAssignment(PartAssignment);
  NewValueStats->SetPartAssignment(NewValueAssignment);

}
