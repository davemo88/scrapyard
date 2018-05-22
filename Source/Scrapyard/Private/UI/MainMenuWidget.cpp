// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"
#include "ScrapyardGameInstance.h"
#include "WidgetTree.h"


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
	UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(World->GetGameInstance());
//	EOnlineMode NewOnlineMode = bIsLAN ? EOnlineMode::LAN : EOnlineMode::Online;
//  GameInstance->SetOnlineMode(EOnlineMode) 
//	GameInstance->HostSession(Player->GetPreferredUniqueNetId(), FName(TEXT("Lol")), true, true, 4);
}

void UMainMenuWidget::OnJoinButtonClicked()
{
	UWorld* World = GetWorld();
	ULocalPlayer* const Player = World->GetFirstLocalPlayerFromController();
	UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(World->GetGameInstance());
	TSharedPtr<const FUniqueNetId> UserId = Player->GetPreferredUniqueNetId();
//	GameInstance->FindSessions(UserId, true, true);
//	GameInstance->JoinSession(UserId, )
}

void UMainMenuWidget::OnQuitButtonClicked()
{
	
}
