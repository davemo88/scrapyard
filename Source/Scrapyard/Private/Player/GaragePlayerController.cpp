// Fill out your copyright notice in the Description page of Project Settings.

#include "GaragePlayerController.h"
#include "Engine/SkeletalMesh.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "UObjectGlobals.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Levels/GarageLevelScriptActor.h"
#include "Parts/RobotPart.h"
#include "Robots/RobotCharacter.h"
#include "UI/GarageWidget.h"
#include "UI/YourPartsWidget.h"
#include "UI/PartCardWidget.h"
#include "UI/RobotStatsWidget.h"

AGaragePlayerController::AGaragePlayerController()
{

}

void AGaragePlayerController::SetupWidget()
{
  UE_LOG(LogController, Log, TEXT("%s::SetupWidget"), *GetName());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());
  GarageWidget = CreateWidget<UGarageWidget>(this, GameInstance->AssetsBP->UIAssetsBP->GarageWidgetBP);
  GarageWidget->YourPartsWidget->CurrentDraft = GameInstance->SoloDraft;
  
  GarageWidget->YourPartsWidget->NewPartCardAdded.AddDynamic(this, &AGaragePlayerController::OnNewCardReady);
   
  GarageWidget->YourPartsWidget->DisplayAll();
  GarageWidget->AddToViewport();

  AGarageLevelScriptActor* GarageActor = Cast<AGarageLevelScriptActor>(GetWorld()->GetLevelScriptActor());
  ARobotCharacter* RobotCharacter = GarageActor->GetRobotCharacter();
//TODO: need to keep track of part assignment after leaving garage, e.g. if you go to testing or battling
//then the existing part assignment / draft should be loaded when the garage loads
  PartAssignment = RobotCharacter->PartAssignment;

//  GarageWidget->InstalledHeadWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &AGaragePlayerController::OnCardAssigned);
//  GarageWidget->InstalledCoreWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &AGaragePlayerController::OnCardAssigned);
//  GarageWidget->InstalledArmsWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &AGaragePlayerController::OnCardAssigned);
//  GarageWidget->InstalledLegsWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &AGaragePlayerController::OnCardAssigned);
//  GarageWidget->InstalledRightHandheldWidget->CompatibleCardDroppedDelegate.AddDynamic(this, &AGaragePlayerController::OnCardAssigned);

//  GarageWidget->RobotStatsWidget->SetRobotStats(RobotCharacter->RobotStats);
//  GarageWidget->RobotStatsWidget->SetNewValueStats(NewValueStats);

  GarageWidget->RobotTestButton->OnClicked.AddDynamic(this, &AGaragePlayerController::GotoGarageTestLevel);

  NewValueAssignment->SetAssignment(PartAssignment);
  NewValueStats->SetPartAssignment(NewValueAssignment);



}

void AGaragePlayerController::OnNewCardReady(UPartCardWidget* CardWidget)
{
  UE_LOG(LogController, Log, TEXT("%s::OnNewCardReady"), *GetName());
  
  CardWidget->CardClickedDelegate.AddDynamic(this, &AGaragePlayerController::OnCardAssigned);
  CardWidget->CardMouseEnteredDelegate.AddDynamic(this, &AGaragePlayerController::OnCardMouseEntered);
  CardWidget->CardMouseLeftDelegate.AddDynamic(this, &AGaragePlayerController::OnCardMouseLeft);
}

void AGaragePlayerController::OnCardAssigned(UPartCardWidget* Card)
{
  UE_LOG(LogController, Log, TEXT("%s::OnCardDoubleClicked"), *GetName());
//  GarageWidget->YourPartsWidget->RemoveDisplayedCard(Card);
  Card->RobotPart->Assign(PartAssignment);
  Card->RobotPart->Assign(NewValueAssignment);
}

void AGaragePlayerController::OnCardMouseEntered(URobotPart* RobotPart)
{
  UE_LOG(LogController, Log, TEXT("%s::OnCardMouseEntered"), *GetName());
  RobotPart->Assign(NewValueAssignment);
}
void AGaragePlayerController::OnCardMouseLeft(URobotPart* RobotPart)
{
  UE_LOG(LogController, Log, TEXT("%s::OnCardMouseLeft"), *GetName());
  NewValueAssignment->SetAssignment(PartAssignment);
}

void AGaragePlayerController::GotoGarageTestLevel()
{
  UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/GarageTestLevel");
}

void AGaragePlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  UE_LOG(LogController, Log, TEXT("%s::EndPlay"), *GetName());
  UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>();
  GameInstance->SoloDraft->PartAssignment = DuplicateObject<UPartAssignment>(PartAssignment, NULL);
  Super::EndPlay(EndPlayReason);
}
