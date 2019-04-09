// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPartAssets.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "Engine/Texture2D.h"
#include "Engine/SkeletalMesh.h"

void URobotPartAssets::LoadAsset(TSoftObjectPtr<UObject> AssetPtr, FStreamableDelegate DelegateToCall)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::LoadAsset"), *GetName());

  if (GameInstance)
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::LoadAsset - GameInstance OK"), *GetName());
    GameInstance->AssetLoader.RequestAsyncLoad(AssetPtr.ToSoftObjectPath(), DelegateToCall);
  }
}

