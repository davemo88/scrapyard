// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardGameInstance.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

UScrapyardGameInstance::UScrapyardGameInstance()
{
// TODO: find the right place for these
	RobotPartAssignment = CreateDefaultSubobject<URobotPartAssignment>(TEXT("RobotPartAssignment"));
	SoloDraft = CreateDefaultSubobject<USoloDraft>(TEXT("SoloDraft"));

//	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UScrapyardGameInstance::OnCreateSessionComplete);
//	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UScrapyardGameInstance::OnStartOnlineGameComplete);
//	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UScrapyardGameInstance::OnFindSessionsComplete);
//	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UScrapyardGameInstance::OnJoinSessionComplete);
//	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UScrapyardGameInstance::OnDestroySessionComplete);
};

void UScrapyardGameInstance::Init()
{
	Super::Init();
}

void UScrapyardGameInstance::Shutdown()
{
	Super::Shutdown();
}

FGameInstancePIEResult UScrapyardGameInstance::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
{
	UE_LOG(LogTemp, Warning, TEXT("StartPlayInEditorGameInstance()"));
	return Super::StartPlayInEditorGameInstance(LocalPlayer, Params);
}

void UScrapyardGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}

AScrapyardGameSession* UScrapyardGameInstance::GetGameSession() const
{
	UWorld* const World = GetWorld();
	if (World)
	{
		AGameModeBase* const Game = World->GetAuthGameMode();
		if (Game)
		{
			return Cast<AScrapyardGameSession>(Game->GameSession);
		}
	}

	return nullptr;
}