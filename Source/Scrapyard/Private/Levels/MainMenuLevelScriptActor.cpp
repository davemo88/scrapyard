// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuLevelScriptActor.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardGameViewportClient.h"

void AMainMenuLevelScriptActor::PreInitializeComponents()
{
	Super::PreInitializeComponents();

//	UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetWorld()->GetGameInstance());

//	GameInstance->SetOnlineMode(EOnlineMode::Offline);

	UE_LOG(LogTemp, Warning, TEXT("MainMenuLevelScriptActor PreInitializeComponents"));
}

void AMainMenuLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("MainMenuLevelScriptActor BeginPlay"));

//	UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(GetWorld()->GetGameInstance());
}