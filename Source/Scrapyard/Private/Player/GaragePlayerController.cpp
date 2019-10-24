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
#include "Game/GarageGameState.h"
#include "Levels/GarageLevelScriptActor.h"
#include "Parts/RobotPart.h"
#include "Robots/RobotCharacter.h"
#include "UI/GarageWidget.h"

AGaragePlayerController::AGaragePlayerController()
{

}

void AGaragePlayerController::SetupWidget()
{
  UE_LOG(LogTemp, Log, TEXT("%s::SetupWidget"), *GetName());
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetGameInstance());

  if (AGarageGameState* GarageGS = GetWorld()->GetGameState<AGarageGameState>())
  {
    GarageWidget = CreateWidget<UGarageWidget>(this, GameInstance->AssetsBP->UIAssetsBP->GarageWidgetBP);
    GarageWidget->AddToViewport();
    GarageWidget->SetSoloDraft(GarageGS->CurrentDraft);
  
//TODO: setup proper event for this
    GarageWidget->RobotTestButton->OnClicked.AddDynamic(this, &AGaragePlayerController::OnTestButtonClicked);
    GarageWidget->BattleButton->OnClicked.AddDynamic(this, &AGaragePlayerController::OnBattleButtonClicked);
  
    GarageWidget->PartAssignedDelegate.AddDynamic(this, &AGaragePlayerController::OnPartAssigned);

    GarageWidget->RedButton->OnClicked.AddDynamic(this, &AGaragePlayerController::SetRedBot);
    GarageWidget->PurpleButton->OnClicked.AddDynamic(this, &AGaragePlayerController::SetPurpleBot);
  }

}

void AGaragePlayerController::OnPartAssigned(URobotPart* Part)
{
  UE_LOG(LogTemp, Log, TEXT("%s::OnPartAssigned"), *GetName());
  if (GetWorld())
  {
    if (AGarageGameState* GarageGS = GetWorld()->GetGameState<AGarageGameState>())
    {
      Part->Assign(GarageGS->CurrentDraft->PartAssignment);
    }
  }
}

void AGaragePlayerController::OnTestButtonClicked()
{
  UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/GarageTestLevel");
}

void AGaragePlayerController::OnBattleButtonClicked()
{
//TODO: use matchmaking service etc
  ClientTravel("scrapyard.xyz//Game/Levels/BattleLevel", ETravelType::TRAVEL_Absolute);
//  ClientTravel("127.0.0.1//Game/Levels/BattleLevel", ETravelType::TRAVEL_Absolute);
}

void AGaragePlayerController::SetRedBot()
{
  FPartAssignmentIDs PartIDs;
  PartIDs.HeadID = 1001;
  PartIDs.CoreID = 2001;
  PartIDs.ArmsID = 3001;
  PartIDs.LegsID = 4001;
  PartIDs.BoosterID = 5001;
  PartIDs.RightHandheldID = 6001;
  if (AGarageGameState* GarageGS = GetWorld()->GetGameState<AGarageGameState>())
  {
    GarageGS->CurrentDraft->PartAssignment->SetAssignment(PartIDs);
  }
}

void AGaragePlayerController::SetPurpleBot()
{
  FPartAssignmentIDs PartIDs;
  PartIDs.HeadID = 1005;
  PartIDs.CoreID = 2005;
  PartIDs.ArmsID = 3005;
  PartIDs.LegsID = 4005;
  PartIDs.BoosterID = 5005;
  PartIDs.RightHandheldID = 6005;
  if (AGarageGameState* GarageGS = GetWorld()->GetGameState<AGarageGameState>())
  {
    GarageGS->CurrentDraft->PartAssignment->SetAssignment(PartIDs);
  }
}
