// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPartAssets.h"
#include "Kismet/GameplayStatics.h"
#include "Game/ScrapyardGameInstance.h"

//template <typename T>
void URobotPartAssets::LoadAsset(TSoftObjectPtr<UObject> AssetPtr, FStreamableDelegate DelegateToCall)
{
  UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(UGameplayStatics::GetGameInstance());

  GameInstance->AssetLoader.RequestAsyncLoad(AssetPtr.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, URobotPartAssets::OnAssetsLoaded));
//  GameInstance->AssetLoader.RequestAsyncLoad(AssetPtr.ToStringReference(), Delegate);
  
}

void URobotPartAssets::OnAssetsLoaded()
{
    
}
