// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardGameInstance.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "GameFramework/GameModeBase.h"

UScrapyardGameInstance::UScrapyardGameInstance()
{
// TODO: find the right place for these
	RobotPartAssignment = CreateDefaultSubobject<URobotPartAssignment>(TEXT("RobotPartAssignment"));
	SoloDraft = CreateDefaultSubobject<USoloDraft>(TEXT("SoloDraft"));

// TODO: best way to get the BP class ref?
// https://forums.unrealengine.com/development-discussion/c-gameplay-programming/15841-access-to-blueprints-default-paramteres
	FStringClassReference DefaultAssetsBPClassRef(TEXT("/Game/ScrapyardDefaultAssetsBP.ScrapyardDefaultAssetsBP_C"));
	if (UClass* DefaultAssetsBPClass =  DefaultAssetsBPClassRef.TryLoadClass<UScrapyardDefaultAssets>())
	{
		UE_LOG(LogTemp, Warning, TEXT("we loaded the default assets bp"));
// new object will use the C++ class defaults, not the BP defaults, which defeats the purpose of setting asset refs in BP
//		UScrapyardDefaultAssets* lol = NewObject<UScrapyardDefaultAssets>(DefaultAssetsBPClass);
		const UScrapyardDefaultAssets* lol = DefaultAssetsBPClass->GetDefaultObject<UScrapyardDefaultAssets>();
		UE_LOG(LogTemp, Warning, TEXT("the teststring is set to: %s"), *lol->TestString)
		UE_LOG(LogTemp, Warning, TEXT("%s"), *lol->DefaultArmsPart->PartName)
	}


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