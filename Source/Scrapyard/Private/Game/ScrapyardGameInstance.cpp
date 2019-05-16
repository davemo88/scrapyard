// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardGameInstance.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Online/ScrapyardGameSession.h"
#include "Game/ScrapyardAssets.h"
#include "Components/Button.h"
#include "SoloDraft.h"

UScrapyardGameInstance* UScrapyardGameInstance::GameInstance = nullptr;

UScrapyardGameInstance::UScrapyardGameInstance()
{
  GameInstance = this;
// TODO: find the right place for these
  SoloDraft = CreateDefaultSubobject<USoloDraft>(TEXT("SoloDraft"));

  PartSingleton = CreateDefaultSubobject<UPartSingleton>(TEXT("PartSingleton"));
};

void UScrapyardGameInstance::Init()
{
  Super::Init();

  InitAssetsBP();
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

void UScrapyardGameInstance::InitAssetsBP()
{
// TODO: best way to get the BP class ref?
// https://forums.unrealengine.com/development-discussion/c-gameplay-programming/15841-access-to-blueprints-default-paramteres
  FStringClassReference AssetsBPClassRef(TEXT("/Game/ScrapyardAssetsBP.ScrapyardAssetsBP_C"));
  if (UClass* AssetsBPClass =  AssetsBPClassRef.TryLoadClass<UScrapyardAssets>())
  {
// NewObject will use the C++ class defaults, not the BP defaults, which defeats the purpose of setting asset refs in BP
    AssetsBP = AssetsBPClass->GetDefaultObject<UScrapyardAssets>();

    AssetsBP->UIAssetsBP = AssetsBP->UIAssetsBPClass->GetDefaultObject<UIAssetsBPClass>();
    AssetsBP->PartsAssetsBP = AssetsBP->PartsAssetsBPClass->GetDefaultObject<PartsAssetsBPClass>();

  }
}
