// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuLevelScriptActor.h"
#include "Game/ScrapyardGameInstance.h"

void AMainMenuLevelScriptActor::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UE_LOG(LogTemp, Warning, TEXT("MainMenuLevelScriptActor PreInitializeComponents"));
}

void AMainMenuLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("MainMenuLevelScriptActor BeginPlay"));

}