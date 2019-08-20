// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageWidget.h"
#include "Scrapyard.h"
#include "Game/ScrapyardGameInstance.h"
#include "Levels/GarageLevelScriptActor.h"
#include "Robots/RobotCharacter.h"
#include "Drafting/SoloDraft.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/BoosterPart.h"
#include "Parts/HandheldPart.h"
#include "UI/YourPartsWidgetBase.h"
#include "UI/RobotStatsWidget.h"

void UGarageWidget::NativeConstruct()
{
  UE_LOG(LogUI, Log, TEXT("%s::NativeConstruct"), *GetName());
  Super::NativeConstruct();

  SetupInstalledPartWidgets();

  YourPartsWidget->NewCardAddedDelegate.AddDynamic(this, &UGarageWidget::OnNewCardReady);
}

void UGarageWidget::SetupInstalledPartWidgets()
{
  InstalledHeadWidget->SetInstalledPartType(UHeadPart::StaticClass());
  InstalledCoreWidget->SetInstalledPartType(UCorePart::StaticClass());
  InstalledArmsWidget->SetInstalledPartType(UArmsPart::StaticClass());
  InstalledLegsWidget->SetInstalledPartType(ULegsPart::StaticClass());
  InstalledBoosterWidget->SetInstalledPartType(UBoosterPart::StaticClass());
  InstalledRightHandheldWidget->SetInstalledPartType(UHandheldPart::StaticClass());

  InstalledHeadWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);
  InstalledCoreWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);
  InstalledArmsWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);
  InstalledLegsWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);
  InstalledBoosterWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);
  InstalledRightHandheldWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);

  InstalledHeadWidget->PartUninstalledDelegate.AddDynamic(this, &UGarageWidget::OnPartUninstalled);
  InstalledCoreWidget->PartUninstalledDelegate.AddDynamic(this, &UGarageWidget::OnPartUninstalled);
  InstalledArmsWidget->PartUninstalledDelegate.AddDynamic(this, &UGarageWidget::OnPartUninstalled);
  InstalledLegsWidget->PartUninstalledDelegate.AddDynamic(this, &UGarageWidget::OnPartUninstalled);
  InstalledBoosterWidget->PartUninstalledDelegate.AddDynamic(this, &UGarageWidget::OnPartUninstalled);
  InstalledRightHandheldWidget->PartUninstalledDelegate.AddDynamic(this, &UGarageWidget::OnPartUninstalled);
}

void UGarageWidget::SetSoloDraft(USoloDraft* NewSoloDraft)
{
  UE_LOG(LogUI, Log, TEXT("%s::SetSoloDraft"), *GetName());
  SoloDraft = NewSoloDraft;

  if (SoloDraft != nullptr)
  {
    UE_LOG(LogUI, Log, TEXT("SoloDraft is ok"), *GetName());
    InstalledHeadWidget->SetInstalledPart(SoloDraft->PartAssignment->GetHead());
    InstalledCoreWidget->SetInstalledPart(SoloDraft->PartAssignment->GetCore());
    InstalledArmsWidget->SetInstalledPart(SoloDraft->PartAssignment->GetArms());
    InstalledLegsWidget->SetInstalledPart(SoloDraft->PartAssignment->GetLegs());
    InstalledBoosterWidget->SetInstalledPart(SoloDraft->PartAssignment->GetBooster());
    InstalledRightHandheldWidget->SetInstalledPart(SoloDraft->PartAssignment->GetRightHandheld());

    SoloDraft->PartAssignment->HeadAssignedDelegate.AddDynamic(InstalledHeadWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->CoreAssignedDelegate.AddDynamic(InstalledCoreWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->ArmsAssignedDelegate.AddDynamic(InstalledArmsWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->LegsAssignedDelegate.AddDynamic(InstalledLegsWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->BoosterAssignedDelegate.AddDynamic(InstalledBoosterWidget, &UInstalledPartWidget::SetInstalledPart);
    SoloDraft->PartAssignment->RightHandheldAssignedDelegate.AddDynamic(InstalledRightHandheldWidget, &UInstalledPartWidget::SetInstalledPart);
  }

  NewValueAssignment = NewObject<UPartAssignment>();
  NewValueStats = NewObject<URobotStats>();

  NewValueAssignment->SetAssignment(SoloDraft->PartAssignment);
  NewValueStats->SetPartAssignment(NewValueAssignment);

//  URobotStats* RobotStats = NewObject<URobotStats>();
//  RobotStats->SetPartAssignment(SoloDraft->PartAssignment);
  if (AGarageLevelScriptActor* GarageLSA = Cast<AGarageLevelScriptActor>(GetWorld()->GetLevelScriptActor()))
  {
    RobotStatsWidget->SetRobotStats(GarageLSA->GetRobotCharacter()->RobotStats);
  }

  RobotStatsWidget->SetNewValueStats(NewValueStats);

  YourPartsWidget->SetCurrentDraft(SoloDraft);
  YourPartsWidget->DisplayUnassignedParts();
}

void UGarageWidget::OnNewCardReady(UCardWidgetBase* CardWidget)
{
  UE_LOG(LogUI, Log, TEXT("%s::OnNewCardReady"), *GetName());
  
  CardWidget->CardClickedDelegate.AddDynamic(this, &UGarageWidget::OnCardAssigned);
  CardWidget->CardMouseEnteredDelegate.AddDynamic(this, &UGarageWidget::OnCardMouseEntered);
  CardWidget->CardMouseLeftDelegate.AddDynamic(this, &UGarageWidget::OnCardMouseLeft);
}

void UGarageWidget::OnCardMouseEntered(UCardWidgetBase* Card)
{
  UE_LOG(LogUI, Log, TEXT("%s::OnCardMouseEntered"), *GetName());
  Card->RobotPart->Assign(NewValueAssignment);
}
void UGarageWidget::OnCardMouseLeft(UCardWidgetBase* Card)
{
  UE_LOG(LogUI, Log, TEXT("%s::OnCardMouseLeft"), *GetName());
  NewValueAssignment->SetAssignment(SoloDraft->PartAssignment);
}

void UGarageWidget::OnCardAssigned(UCardWidgetBase* Card)
{
  UE_LOG(LogUI, Log, TEXT("%s::OnCardAssigned"), *GetName());
  UE_LOG(LogUI, VeryVerbose, TEXT("%s::OnCardAssigned - %s"), *GetName(), *Card->RobotPart->PartName.ToString());
  PartAssignedDelegate.Broadcast(Card->RobotPart);
  YourPartsWidget->RemoveDisplayedCard(Card);
}

void UGarageWidget::OnPartUninstalled(URobotPart* UninstalledPart)
{
  if (!UninstalledPart->IsDefaultPart())
  {
    YourPartsWidget->DisplayPart(UninstalledPart);  
  }
}
