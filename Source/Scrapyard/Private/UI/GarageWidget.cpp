// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/PanelWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "UI/PartCardWidget.h"
#include "SoloDraft.h"

void UGarageWidget::SetSoloDraft(USoloDraft* _SoloDraft)
{
	SoloDraft = _SoloDraft;
}

void UGarageWidget::SetPartAssignment(URobotPartAssignment* _PartAssignment)
{
	PartAssignment = _PartAssignment;
}

void UGarageWidget::DisplayHeads()
{
	RemovePartCards();
	AddPartCards<UHeadPart>(SoloDraft->DraftedHeads);
}

void UGarageWidget::DisplayCores()
{
	RemovePartCards();
	AddPartCards<UCorePart>(SoloDraft->DraftedCores);

}

void UGarageWidget::DisplayArms()
{
	RemovePartCards();
	AddPartCards<UArmsPart>(SoloDraft->DraftedArms);
}

void UGarageWidget::DisplayLegs()
{
	RemovePartCards();
	AddPartCards<ULegsPart>(SoloDraft->DraftedLegs);
}

void UGarageWidget::GotoGarageTestLevel()
{
	UGameplayStatics::OpenLevel(GetOwningPlayer()->GetWorld(), "GarageTestLevel");
}

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

template <class T>
void UGarageWidget::AddPartCards(TArray<T*> Parts)
{
	UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetOwningPlayer()->GetGameInstance());
	UPanelWidget* PartCardBox = Cast<UPanelWidget>(GetWidgetFromName(FName(TEXT("PartCardBox"))));
	for (int i = 0; i < Parts.Num(); ++i)
	{
		UPartCardWidget* PartCardWidget = CreateWidget<UPartCardWidget>(GetOwningPlayer(), GameInstance->DefaultAssetsBP->PartCardWidgetBP);
		PartCardWidget->SetRobotPart(Parts[i]);
		PartCardWidget->PartCardClickedDelegate.AddDynamic(this, &UGarageWidget::AssignPart);
		PartCardBox->AddChild(PartCardWidget);
	}
}

void UGarageWidget::AssignPart(URobotPart* Part)
{
	Part->Assign(PartAssignment);
}

