// Fill out your copyright notice in the Description page of Project Settings.


#include "SoloDraftWidget.h"
#include "UI/YourPartsWidget.h"
#include "Blueprint/WidgetTree.h"

void USoloDraftWidget::NativeConstruct()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::NativeConstruct"), *GetName());
//  UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget()); 
//
//  YourPartsWidget = WidgetTree->ConstructWidget<UYourPartsWidget>(UYourPartsWidget::StaticClass(), TEXT("YourPartsWidget"));
//
//  RootWidget->AddChild(YourPartsWidget);
}


