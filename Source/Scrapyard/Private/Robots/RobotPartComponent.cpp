// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartComponent.h"
#include "Scrapyard.h"
#include "Game/ScrapyardGameInstance.h"
#include "Game/ScrapyardAssets.h"
#include "Parts/RobotPart.h"
#include "Parts/PartAssets.h"
#include "Materials/Material.h"
#include "Components/MeshComponent.h"

void URobotPartComponent::BeginPlay()
{
  Super::BeginPlay();
  UE_LOG(LogParts, Log, TEXT("%s::BeginPlay"), *GetName());
}

void URobotPartComponent::SetRobotPart(URobotPart* NewRobotPart)
{
  if (NewRobotPart != nullptr)
  {
    UE_LOG(LogParts, Log, TEXT("%s::SetRobotPart"), *GetName());
    RobotPart = NewRobotPart;
    if (GetOwner() != NULL && GetWorld() != NULL && (!GetOwner()->HasAuthority() || GetWorld()->GetNetMode() == ENetMode::NM_Standalone))
    {
      UE_LOG(LogParts, Log, TEXT("%s::SetRobotPart - Loading Assets"), *GetName());
      SetSkeletalMesh(UScrapyardGameInstance::AssetsBP->GetAsset<USkeletalMesh>(RobotPart->SkeletalMesh));
      SetMaterial(0,UScrapyardGameInstance::AssetsBP->GetAsset<UMaterial>(RobotPart->MajorMaterial));
    }
  }
}
