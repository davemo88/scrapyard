// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrapyardGameInstance.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Online/ScrapyardGameSession.h"
#include "Game/ScrapyardDefaultAssets.h"
#include "Components/Button.h"
#include "Parts/RobotPartAssets.h"
#include "Parts/RobotPart.h"
#include "Parts/HeadPart.h"
#include "Parts/CorePart.h"
#include "Parts/ArmsPart.h"
#include "Parts/LegsPart.h"
#include "Parts/Manufacturer.h"
#include "SoloDraft.h"

UScrapyardGameInstance* UScrapyardGameInstance::GameInstance = nullptr;

UScrapyardGameInstance::UScrapyardGameInstance()
{
  GameInstance = this;
// TODO: find the right place for these
  SoloDraft = CreateDefaultSubobject<USoloDraft>(TEXT("SoloDraft"));
};

void UScrapyardGameInstance::Init()
{
  Super::Init();

//TODO: rename to wigdets
  InitDefaultAssetsBP();
  InitRobotPartAssetsBP();
  Manufacturers.InitManufacturers();
  InitPartDB();
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

void UScrapyardGameInstance::InitDefaultAssetsBP()
{
// TODO: best way to get the BP class ref?
// https://forums.unrealengine.com/development-discussion/c-gameplay-programming/15841-access-to-blueprints-default-paramteres
  FStringClassReference DefaultAssetsBPClassRef(TEXT("/Game/ScrapyardDefaultAssetsBP.ScrapyardDefaultAssetsBP_C"));
  if (UClass* DefaultAssetsBPClass =  DefaultAssetsBPClassRef.TryLoadClass<UScrapyardDefaultAssets>())
  {
// NewObject will use the C++ class defaults, not the BP defaults, which defeats the purpose of setting asset refs in BP
    DefaultAssetsBP = DefaultAssetsBPClass->GetDefaultObject<UScrapyardDefaultAssets>();
  }
}

void UScrapyardGameInstance::InitRobotPartAssetsBP()
{
  FStringClassReference RobotPartAssetsBPClassRef(TEXT("/Game/RobotPartAssetsBP.RobotPartAssetsBP_C"));
  if (UClass* RobotPartAssetsBPClass = RobotPartAssetsBPClassRef.TryLoadClass<URobotPartAssets>())
  {
    RobotPartAssetsBP = RobotPartAssetsBPClass->GetDefaultObject<URobotPartAssets>();
    if (RobotPartAssetsBP)
    {
      UE_LOG(LogTemp, Warning, TEXT("RobotPartAssetsBP was loaded"));
      URobotPart::RobotPartAssetsBP = RobotPartAssetsBP;
// TODO: this is a hack since getting game instance outside of actor is mysterious
//      RobotPartAssetsBP->GameInstance = this;
    }
    else
    {
      UE_LOG(LogTemp, Warning, TEXT("RobotPartAssetsBP was NOT loaded"));
    }
  }
}

void UScrapyardGameInstance::InitPartDB()
{
  PartDB.AddPart(
    UHeadPart::NewHead(
      1000,
      NSLOCTEXT("SY", "DefaultHeadName", "Default Head"),
      Manufacturers.DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      nullptr,
      URobotPart::RobotPartAssetsBP->HeadPart_Default_SkeletalMesh,
      URobotPart::RobotPartAssetsBP->DefaultMaterial,
      10,
      1));
  PartDB.AddPart(
    UCorePart::NewCore(
      2000,
      NSLOCTEXT("SY", "DefaultCoreName", "Default Core"),
      Manufacturers.DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      nullptr,
      URobotPart::RobotPartAssetsBP->CorePart_Default_SkeletalMesh,
      URobotPart::RobotPartAssetsBP->DefaultMaterial,
      1000,
      500,
      500,
      10));
  PartDB.AddPart(
    UArmsPart::NewArms(
      3000,
      NSLOCTEXT("SY", "DefaultArmsName", "Default Arms"),
      Manufacturers.DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      nullptr,
      URobotPart::RobotPartAssetsBP->ArmsPart_Default_SkeletalMesh,
      URobotPart::RobotPartAssetsBP->DefaultMaterial));
  PartDB.AddPart(
    ULegsPart::NewLegs(
      4000,
      NSLOCTEXT("SY", "DefaultLegsName", "Default Legs"),
      Manufacturers.DefaultManufacturer,
      nullptr,
      100,
      50,
      100,
      nullptr,
      URobotPart::RobotPartAssetsBP->LegsPart_Default_SkeletalMesh,
      URobotPart::RobotPartAssetsBP->DefaultMaterial,
      1000,
      500,
      10));
}
