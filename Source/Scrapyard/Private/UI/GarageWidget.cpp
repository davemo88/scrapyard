// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Game/ScrapyardGameInstance.h"
#include "Parts/ArmsPart.h"
#include "SoloDraft.h"
#include "UI/PartCardWidget.h"

void UGarageWidget::RemovePartCards()
{
	TArray <UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UPartCardWidget::StaticClass(), false);
	for (int i = 0; i < FoundWidgets.Num(); ++i)
	{
		UUserWidget* Widget = FoundWidgets[i];
		Widget->RemoveFromParent();
	}
}

void UGarageWidget::DisplayArms()
{
	for (int i = 0; i < SoloDraft->DraftedArms.Num(); ++i)
	{
		UPartCardWidget* Widget = CreateWidget<UPartCardWidget>(GetWorld(), UPartCardWidget::StaticClass());
	}
}
