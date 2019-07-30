// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageWidget.h"
#include "Scrapyard.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/HandheldPart.h"
#include "UI/YourPartsWidget.h"
#include "UI/RobotStatsWidget.h"

void UGarageWidget::NativeConstruct()
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();

  InstalledHeadWidget->SetInstalledPartType(UHeadPart::StaticClass());
  InstalledCoreWidget->SetInstalledPartType(UCorePart::StaticClass());
  InstalledArmsWidget->SetInstalledPartType(UArmsPart::StaticClass());
  InstalledLegsWidget->SetInstalledPartType(ULegsPart::StaticClass());
  InstalledRightHandheldWidget->SetInstalledPartType(UHandheldPart::StaticClass());

  InstalledHeadWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);
  InstalledCoreWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);
  InstalledArmsWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);
  InstalledLegsWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);
  InstalledRightHandheldWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);

  YourPartsWidget->NewPartCardAdded.AddDynamic(this, &UGarageWidget::OnNewCardReady);
}

void UGarageWidget::SetSoloDraft(USoloDraft* NewSoloDraft)
{
  UE_LOG(LogUI, Log, TEXT("%s::SetSoloDraft"), *GetName());
  SoloDraft = NewSoloDraft;
  YourPartsWidget->CurrentDraft = SoloDraft;

  if (SoloDraft != nullptr)
  {
    UE_LOG(LogUI, Log, TEXT("SoloDraft is ok"), *GetName());
    InstalledHeadWidget->SetInstalledPart(SoloDraft->PartAssignment->GetHead());
    InstalledCoreWidget->SetInstalledPart(SoloDraft->PartAssignment->GetCore());
    InstalledArmsWidget->SetInstalledPart(SoloDraft->PartAssignment->GetArms());
    InstalledLegsWidget->SetInstalledPart(SoloDraft->PartAssignment->GetLegs());
    InstalledRightHandheldWidget->SetInstalledPart(SoloDraft->PartAssignment->GetRightHandheld());

    SoloDraft->PartAssignment->HeadAssignmentChangedDelegate.AddDynamic(InstalledHeadWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->CoreAssignmentChangedDelegate.AddDynamic(InstalledCoreWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->ArmsAssignmentChangedDelegate.AddDynamic(InstalledArmsWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->LegsAssignmentChangedDelegate.AddDynamic(InstalledLegsWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->RightHandheldAssignmentChangedDelegate.AddDynamic(InstalledRightHandheldWidget, &UInstalledPartWidget::SetInstalledPart);
  }

  NewValueAssignment = NewObject<UPartAssignment>();
  NewValueStats = NewObject<URobotStats>();

  NewValueAssignment->SetAssignment(SoloDraft->PartAssignment);
  NewValueStats->SetPartAssignment(NewValueAssignment);

  URobotStats* RobotStats = NewObject<URobotStats>();
  RobotStats->SetPartAssignment(SoloDraft->PartAssignment);
  RobotStatsWidget->SetRobotStats(RobotStats);
  RobotStatsWidget->SetNewValueStats(NewValueStats);

  YourPartsWidget->DisplayAll();
}

void UGarageWidget::OnNewCardReady(UPartCardWidget* CardWidget)
{
  UE_LOG(LogController, Log, TEXT("%s::OnNewCardReady"), *GetName());
  
  CardWidget->CardClickedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);
  CardWidget->CardMouseEnteredDelegate.AddDynamic(this, &UGarageWidget::OnCardMouseEntered);
  CardWidget->CardMouseLeftDelegate.AddDynamic(this, &UGarageWidget::OnCardMouseLeft);
}

void UGarageWidget::OnCardMouseEntered(URobotPart* RobotPart)
{
  UE_LOG(LogController, Log, TEXT("%s::OnCardMouseEntered"), *GetName());
  RobotPart->Assign(NewValueAssignment);
}
void UGarageWidget::OnCardMouseLeft(URobotPart* RobotPart)
{
  UE_LOG(LogController, Log, TEXT("%s::OnCardMouseLeft"), *GetName());
  NewValueAssignment->SetAssignment(SoloDraft->PartAssignment);
}

void UGarageWidget::OnCardAssigned(UPartCardWidget* Card)
{
  UE_LOG(LogController, Log, TEXT("%s::OnCardAssigned"), *GetName());
  PartAssignedDelegate.Broadcast(Card->RobotPart);
}
