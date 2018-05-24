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
	UGameplayStatics::OpenLevel(World, "SoloDraftLevel");
}

void UMainMenuWidget::OnGarageButtonClicked()
{
	UWorld* World = GetWorld();
	UGameplayStatics::OpenLevel(World, "GarageLevel");
}

void UMainMenuWidget::OnHostButtonClicked()
{
	UWorld* World = GetWorld();
	ULocalPlayer* const Player = World->GetFirstLocalPlayerFromController();
	UScrapyardGameInstance* GameInstance = World->GetGameInstance<UScrapyardGameInstance>();
	AScrapyardGameSession* GameSession = GameInstance->GetGameSession();
	GameSession->HostSession(Player->GetPreferredUniqueNetId(), FName(TEXT("TestSession")), true, true, 2);
}

void UMainMenuWidget::OnJoinButtonClicked()
{
	UWorld* World = GetWorld();
	ULocalPlayer* const Player = World->GetFirstLocalPlayerFromController();
	UScrapyardGameInstance* GameInstance = World->GetGameInstance<UScrapyardGameInstance>();
	AScrapyardGameSession* GameSession = GameInstance->GetGameSession();
	GameSession->FindSessions(Player->GetPreferredUniqueNetId(), FName(TEXT("TestSession")), true, true);
}

void UMainMenuWidget::OnQuitButtonClicked()
{
	
}
