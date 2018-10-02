// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartComponent.h"
#include "Parts/RobotPartAssets.h"

void URobotPartComponent::BeginPlay()
{
  Super::BeginPlay();
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());

  USkeletalMesh* Mesh = GetSkeletalMesh();
  if (Mesh != NULL)
  {
    SetSkeletalMesh(Mesh);
  }
}

URobotPartAssets* URobotPartComponent::GetRobotPartAssets()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetRobotPartAssets"), *GetName());
  UWorld* World = GetWorld();
  if (World)
  {
    UScrapyardGameInstance* GameInstance = Cast<UScrapyardGameInstance>(World->GetGameInstance());
    return GameInstance->RobotPartAssetsBP;
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("World was null for GetRobotPartAssets"));
  }
  return nullptr;
}

void URobotPartComponent::SetRobotPart(URobotPart* _RobotPart)
{
  RobotPart = _RobotPart;
}

USkeletalMesh* URobotPartComponent::GetSkeletalMesh()
{
  UE_LOG(LogTemp, Warning, TEXT("%s::GetSkeletalMesh"), *GetName());
  return nullptr; 
}
