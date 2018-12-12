// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPartAssets.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Game/ScrapyardGameInstance.h"

//template <typename T>
void URobotPartAssets::LoadAsset(TSoftObjectPtr<UObject> AssetPtr, FStreamableDelegate DelegateToCall)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::LoadAsset"), *GetName());

  if (GameInstance)
  {
    UE_LOG(LogTemp, Warning, TEXT("GameInstance For LoadAsset OK"));
    GameInstance->AssetLoader.RequestAsyncLoad(AssetPtr.ToSoftObjectPath(), DelegateToCall);
  }
}

//TODO: maybe can simplify this by just calling LoadSynchronous on the TSoftObjectPtr
template<typename T>
T* URobotPartAssets::LoadAssetSynchronous(TSoftObjectPtr<UObject> SoftObjectPtr)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::LoadAssetSynchronous"), *GetName());

  T* Asset = nullptr;

  if (!SoftObjectPtr.IsNull() && GameInstance)
  {
    UE_LOG(LogTemp, Warning, TEXT("GameInstance For LoadAsset OK"));
    TSharedPtr<FStreamableHandle> StreamableHandle = GameInstance->AssetLoader.RequestSyncLoad(SoftObjectPtr.ToSoftObjectPath());
    Asset = Cast<T>(StreamableHandle->GetLoadedAsset());
  }

  return Asset;
}
