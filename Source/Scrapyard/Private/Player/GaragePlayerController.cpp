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
  NewValueAssignment = CreateDefaultSubobject<UPartAssignment>(TEXT("NewValueAssignment"));
  NewValueStats = CreateDefaultSubobject<URobotStats>(TEXT("NewValueStats"));
}

void AGaragePlayerController::SetupWidget()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetupWidget"), *GetName());
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

  GarageWidget->RobotStatsWidget->SetRobotStats(RobotCharacter->RobotStats);
  GarageWidget->RobotStatsWidget->SetNewValueStats(NewValueStats);

  GarageWidget->RobotTestButton->OnClicked.AddDynamic(this, &AGaragePlayerController::GotoGarageTestLevel);

  NewValueAssignment->SetAssignment(PartAssignment);
  NewValueStats->SetPartAssignment(NewValueAssignment);

}

void AGaragePlayerController::OnNewCardReady(UPartCardWidget* CardWidget)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnNewCardReady"), *GetName());
  
//  CardWidget->RobotPart->GetSkeletalMesh();
//  CardWidget->RobotPart->GetMajorMaterial();
  CardWidget->CardDoubleClickedDelegate.AddDynamic(this, &AGaragePlayerController::OnCardDoubleClicked);
  CardWidget->CardMouseEnteredDelegate.AddDynamic(this, &AGaragePlayerController::OnCardMouseEntered);
  CardWidget->CardMouseLeftDelegate.AddDynamic(this, &AGaragePlayerController::OnCardMouseLeft);
}

void AGaragePlayerController::OnCardDoubleClicked(URobotPart* RobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnCardDoubleClicked"), *GetName());
  RobotPart->Assign(PartAssignment);
}

void AGaragePlayerController::OnCardMouseEntered(URobotPart* RobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnCardMouseEntered"), *GetName());
  RobotPart->Assign(NewValueAssignment);
//  NewValueAssignment->GetPartAssignmentIDs();
}
void AGaragePlayerController::OnCardMouseLeft(URobotPart* RobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::OnCardMouseLeft"), *GetName());
  NewValueAssignment->SetAssignment(PartAssignment);
//  NewValueAssignment->GetPartAssignmentIDs();
}

void AGaragePlayerController::GotoGarageTestLevel()
{
  UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/GarageTestLevel");
}

void AGaragePlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::EndPlay"), *GetName());
//TODO: this is just here to print some stuff to logs i guess
  PartAssignment->GetPartAssignmentIDs();
  UScrapyardGameInstance* GameInstance = GetWorld()->GetGameInstance<UScrapyardGameInstance>();
  GameInstance->PartAssignment = DuplicateObject<UPartAssignment>(PartAssignment, NULL);
  Super::EndPlay(EndPlayReason);
}

