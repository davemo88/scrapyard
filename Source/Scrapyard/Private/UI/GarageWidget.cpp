// Fill out your copyright notice in the Description page of Project Settings.

#include "GarageWidget.h"
#include "UObjectGlobals.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/PanelWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "Robots/RobotBodyGarage.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "UI/PartCardWidget.h"
#include "SoloDraft.h"

void UGarageWidget::DisplayHeads()
{
//  AddPartCards<UHeadPart>(SoloDraft->DraftedHeads);
}

void UGarageWidget::DisplayCores()
{
// AddPartCards<UCorePart>(SoloDraft->DraftedCores);

}

void UGarageWidget::DisplayArms()
{
//  AddPartCards<UArmsPart>(SoloDraft->DraftedArms);
}

void UGarageWidget::DisplayLegs()
{
// AddPartCards<ULegsPart>(SoloDraft->DraftedLegs);
}

void UGarageWidget::GotoGarageTestLevel()
{
//  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetOwningPlayer()->GetGameInstance());
//  GameInstance->RobotBodyComponent = DuplicateObject<URobotBodyComponent>(RobotBodyGarage->RobotBodyComponent, nullptr);// GetOwningPlayer()->GetWorld());
  UGameplayStatics::OpenLevel(GetOwningPlayer()->GetWorld(), "/Game/Levels/GarageTestLevel");
}

//void UGarageWidget::RemovePartCards()
//{
//  TArray <UUserWidget*> FoundWidgets;
//  UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UPartCardWidget::StaticClass(), false);
//  for (int i = 0; i < FoundWidgets.Num(); ++i)
//  {
//    UUserWidget* Widget = FoundWidgets[i];
//    Widget->RemoveFromParent();
//  }
//}
//
//template <class T>
//void UGarageWidget::AddPartCards(TArray<T*> Parts)
//{
//  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetOwningPlayer()->GetGameInstance());
//  UPanelWidget* PartCardBox = Cast<UPanelWidget>(GetWidgetFromName(FName(TEXT("PartCardBox"))));
//  for (int i = 0; i < Parts.Num(); ++i)
//  {
//    UPartCardWidget* PartCardWidget = CreateWidget<UPartCardWidget>(GetOwningPlayer(), GameInstance->DefaultAssetsBP->PartCardWidgetBP);
//    PartCardWidget->SetRobotPart(Parts[i]);
//    PartCardWidget->PartCardClickedDelegate.AddDynamic(this, &UGarageWidget::AssignPart);
//    PartCardBox->AddChild(PartCardWidget);
//  }
//}

