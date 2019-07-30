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
#include "UI/YourPartsWidget.h"
#include "UI/PartCardWidget.h"
#include "UI/RobotStatsWidget.h"

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
  
    GarageWidget->RobotTestButton->OnClicked.AddDynamic(this, &AGaragePlayerController::GotoGarageTestLevel);
  
    GarageWidget->PartAssignedDelegate.AddDynamic(this, &AGaragePlayerController::OnPartAssigned);
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

void AGaragePlayerController::GotoGarageTestLevel()
{
  UGameplayStatics::OpenLevel(GetWorld(), "/Game/Levels/GarageTestLevel");
}
