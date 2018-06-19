// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Game/ScrapyardGameInstance.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainMenuWidget::OnDraftButtonClicked()
{
	UWorld* World = GetWorld();
	UGameplayStatics::OpenLevel(World, "/Game/Levels/SoloDraftLevel");
}

void UMainMenuWidget::OnGarageButtonClicked()
{
	UWorld* World = GetWorld();
	UGameplayStatics::OpenLevel(World, "/Game/Levels/GarageLevel");
}

void UMainMenuWidget::OnHostButtonClicked()
{
	UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetOwningPlayer()->GetGameInstance());
	AScrapyardGameSession* GameSession = GameInstance->GetGameSession();
	GameSession->HostSession(GetOwningLocalPlayer()->GetPreferredUniqueNetId(), FName(TEXT("TestSession")), true, true, 2);
}

void UMainMenuWidget::OnJoinButtonClicked()
{
//	UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetOwningPlayer()->GetGameInstance());
//	AScrapyardGameSession* GameSession = GameInstance->GetGameSession();
//	GameSession->FindSessions(GetOwningLocalPlayer()->GetPreferredUniqueNetId(), FName(TEXT("DedicatedSession")), true, false);
	APlayerController* Player = GetOwningPlayer();
	Player->ClientTravel("35.171.154.29//Game/Levels/BattleLevel", ETravelType::TRAVEL_Absolute);
}

void UMainMenuWidget::OnQuitButtonClicked()
{
	
}
