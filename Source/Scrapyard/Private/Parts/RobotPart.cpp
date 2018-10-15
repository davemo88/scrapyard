// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPart.h"
#include "RobotPartAssets.h"
#include "Engine/SkeletalMesh.h"

//URobotPartAssets* URobotPart::GetRobotPartAssets()
//{
//  UWorld* World = GetWorld();
//  UE_LOG(LogTemp, Warning, TEXT("URobotPartHelper::GetRobotPartAssets"), *GetName());
//  if (World)
//  {
//    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(World->GetGameInstance());
//    return GameInstance->RobotPartAssetsBP;
//  }
//  else
//  {
//    UE_LOG(LogTemp, Warning, TEXT("World was null"));
//  }
//  return nullptr;
//}

URobotPartAssets* URobotPart::RobotPartAssetsBP = nullptr;

USkeletalMesh* URobotPart::GetSkeletalMesh()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetSkeletalMesh"), *GetName());

  if (SkeletalMesh == NULL && URobotPart::RobotPartAssetsBP != NULL)
  {
    URobotPart::RobotPartAssetsBP->LoadAsset(GetSkeletalMeshAssetPtr(), FStreamableDelegate::CreateUObject(this, &URobotPart::OnSkeletalMeshAssetLoaded));
  }

  return SkeletalMesh;
}

void URobotPart::OnSkeletalMeshAssetLoaded()
{
  SkeletalMesh = GetSkeletalMeshAssetPtr().Get();

}

