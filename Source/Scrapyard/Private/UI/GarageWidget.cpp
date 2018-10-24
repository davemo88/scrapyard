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

void UGarageWidget::GotoGarageTestLevel()
{
//  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetOwningPlayer()->GetGameInstance());
//  GameInstance->RobotBodyComponent = DuplicateObject<URobotBodyComponent>(RobotBodyGarage->RobotBodyComponent, nullptr);// GetOwningPlayer()->GetWorld());
  UGameplayStatics::OpenLevel(GetOwningPlayer()->GetWorld(), "/Game/Levels/GarageTestLevel");
}
