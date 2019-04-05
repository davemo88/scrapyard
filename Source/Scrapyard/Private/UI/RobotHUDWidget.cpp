// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotHUDWidget.h"
#include "Robots/RobotCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine.h"

void URobotHUDWidget::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
  Super::NativeTick(MyGeometry, InDeltaTime);
// widgets don't tick when they aren't shown
// so can avoid this null check if this widget can't be shown without RobotCharacter being set
// maybe override its add to viewport method to check first?
  if (RobotCharacter != NULL)
  {
// TODO: can do this manually whenever actually using power
    UpdatePowerBar(); 
//    UpdateTargetingWidget();
  }

}

void URobotHUDWidget::SetRobotCharacter(ARobotCharacter* NewRobotCharacter)
{
  RobotCharacter = NewRobotCharacter;
  UpdateHitPoints();
  UpdatePowerBar();
  RobotCharacter->HitPointsChangedDelegate.AddDynamic(this, &URobotHUDWidget::UpdateHitPoints);
  RobotCharacter->PowerChangedDelegate.AddDynamic(this, &URobotHUDWidget::UpdatePowerBar);
}

void URobotHUDWidget::UpdatePowerBar()
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::UpdatePowerBar"), *GetName());
  PowerText->SetText(FText::AsNumber(RobotCharacter->Power));
  PowerBar->SetPercent((float)RobotCharacter->Power / (float)RobotCharacter->RobotStats->MaxPower);
}

void URobotHUDWidget::UpdateHitPoints()
{
  HitPointsText->SetText(FText::AsNumber(RobotCharacter->HitPoints));
}

void URobotHUDWidget::UpdateTargetingWidget()
{
//  UE_LOG(LogTemp, Warning, TEXT("%s::UpdateTargetingWidget"), *GetName());
//  if (TargetingWidget != nullptr)
//  {
//    FVector RelativeCenter = FVector(RobotCharacter->RobotTargetingComponent->GetRange(),0,0);
//    FVector WorldCenter = RobotCharacter->GetActorLocation() + RobotCharacter->GetViewRotation().RotateVector(RelativeCenter);
//    UE_LOG(LogTemp, Warning, TEXT("%s::UpdateTargetingWidget RelativeCenter - %s"), *GetName(), *RelativeCenter.ToString());
//    UE_LOG(LogTemp, Warning, TEXT("%s::UpdateTargetingWidget WorldCenter - %s"), *GetName(), *WorldCenter.ToString());
//
//    FVector2D CenterScreenLoc;
//    FVector2D EdgeScreenLoc;
//
////    FVector RelativeEdge = FVector(RobotCharacter->RobotTargetingComponent->GetRange(),0,);
//
//    APlayerController* PC = GetOwningPlayer();
////    bool Projection = PC->ProjectWorldLocationToScreen(WorldCenter, ScreenLoc);
//    bool CenterProjection = UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PC, WorldCenter, CenterScreenLoc);
//    bool EdgeProjection = UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PC, WorldCenter, EdgeScreenLoc);
//    if (CenterProjection)
//    {
//      UE_LOG(LogTemp, Warning, TEXT("Set Targeting Widget Position - %s"), *CenterScreenLoc.ToString());
////      TargetingWidget->SetPositionInViewport(ScreenLoc);
//      UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(TargetingWidget->Slot);
//      if (CanvasSlot)
//      {
//        CanvasSlot->SetPosition(CenterScreenLoc);
////        CanvasSlot->SetAutoSize(true);
//      }
//    }
//  }
}

//
//void URobotHUDWidget::SetHitPointsText(FText NewHitPointsText)
//{
//  HitPointsText->SetText(NewHitPointsText);
//}

void URobotHUDWidget::SetTargetingWidget(UTargetingWidget* NewTargetingWidget)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetTargetingWidget"), *GetName());
  if (TargetingWidget)
  {
    TargetingWidget->RemoveFromParent();
  }
  TargetingWidget = NewTargetingWidget;
  HUDPanel->AddChildToCanvas(TargetingWidget);
  UpdateTargetingWidget();
}
