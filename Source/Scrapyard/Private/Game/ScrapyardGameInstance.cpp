// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardGameInstance.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "Parts/RobotPartAssets.h"
#include "Parts/RobotPart.h"
#include "SoloDraft.h"

UScrapyardGameInstance::UScrapyardGameInstance()
{
// TODO: find the right place for these
  RobotBodyComponent = CreateDefaultSubobject<URobotBodyComponent>(TEXT("RobotBodyComponent"));
  SoloDraft = CreateDefaultSubobject<USoloDraft>(TEXT("SoloDraft"));

// TODO: best way to get the BP class ref?
// https://forums.unrealengine.com/development-discussion/c-gameplay-programming/15841-access-to-blueprints-default-paramteres
  FStringClassReference DefaultAssetsBPClassRef(TEXT("/Game/ScrapyardDefaultAssetsBP.ScrapyardDefaultAssetsBP_C"));
  if (UClass* DefaultAssetsBPClass =  DefaultAssetsBPClassRef.TryLoadClass<UScrapyardDefaultAssets>())
  {
// NewObject will use the C++ class defaults, not the BP defaults, which defeats the purpose of setting asset refs in BP
//    UScrapyardDefaultAssets* lol = NewObject<UScrapyardDefaultAssets>(DefaultAssetsBPClass);
    DefaultAssetsBP = DefaultAssetsBPClass->GetDefaultObject<UScrapyardDefaultAssets>();
  }

  FStringClassReference RobotPartAssetsBPClassRef(TEXT("/Game/RobotPartAssetsBP.RobotPartAssetsBP_C"));
  if (UClass* RobotPartAssetsBPClass = RobotPartAssetsBPClassRef.TryLoadClass<URobotPartAssets>())
  {
// NewObject will use the C++ class defaults, not the BP defaults, which defeats the purpose of setting asset refs in BP
//    UScrapyardDefaultAssets* lol = NewObject<UScrapyardDefaultAssets>(DefaultAssetsBPClass);
    RobotPartAssetsBP = RobotPartAssetsBPClass->GetDefaultObject<URobotPartAssets>();
    if (RobotPartAssetsBP)
    {
      UE_LOG(LogTemp, Warning, TEXT("RobotPartAssetsBP was loaded"));
// TODO: this is a hack since getting game instance outside of actor is mysterious
      RobotPartAssetsBP->GameInstance = this;
    }
    else
    {
      UE_LOG(LogTemp, Warning, TEXT("RobotPartAssetsBP was NOT loaded"));
    }
  }
  URobotPart::RobotPartAssetsBP = RobotPartAssetsBP;
};

void UScrapyardGameInstance::Init()
{
  Super::Init();
}

void UScrapyardGameInstance::Shutdown()
{
  Super::Shutdown();
}

//FGameInstancePIEResult UScrapyardGameInstance::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
//{
//  UE_LOG(LogTemp, Warning, TEXT("StartPlayInEditorGameInstance()"));
//  return Super::StartPlayInEditorGameInstance(LocalPlayer, Params);
//}

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
