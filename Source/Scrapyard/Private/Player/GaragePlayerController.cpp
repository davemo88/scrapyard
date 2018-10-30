// Fill out your copyright notice in the Description page of Project Settings.

#include "GaragePlayerController.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "UObjectGlobals.h"
#include "Blueprint/UserWidget.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "Levels/GarageLevelScriptActor.h"
#include "Robots/RobotBodyGarage.h"
#include "UI/GarageWidget.h"
#include "UI/YourPartsWidget.h"
#include "UI/PartCardWidget.h"

void AGaragePlayerController::SetupWidget()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetupWidget"), *GetName());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  GarageWidget = CreateWidget<UGarageWidget>(this, GameInstance->DefaultAssetsBP->GarageWidgetBP);
  GarageWidget->YourPartsWidget->CurrentDraft = GameInstance->SoloDraft;
  
  GarageWidget->YourPartsWidget->NewPartCardAdded.AddDynamic(this, &AGaragePlayerController::OnNewCardReady);
   
  GarageWidget->YourPartsWidget->DisplayAll();
  GarageWidget->AddToViewport();

  AGarageLevelScriptActor* GarageActor = Cast<AGarageLevelScriptActor>(GetWorld()->GetLevelScriptActor());
  ARobotBodyGarage* RobotBodyGarage = GarageActor->GetRobotBodyGarage();
  PartAssignment = RobotBodyGarage->RobotBodyComponent->PartAssignment;
  RobotBodyGarage->RobotStats->SetPartAssignment(PartAssignment);
}

void AGaragePlayerController::OnNewCardReady(UPartCardWidget* CardWidget)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnNewCardReady"), *GetName());
  
  CardWidget->RobotPart->GetSkeletalMesh();
  CardWidget->RobotPart->GetMajorMaterial();
  CardWidget->CardDoubleClickedDelegate.AddDynamic(this, &AGaragePlayerController::OnCardDoubleClicked);
}

void AGaragePlayerController::OnCardDoubleClicked(URobotPart* RobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnCardDoubleClicked"), *GetName());
  RobotPart->Assign(PartAssignment);
}




