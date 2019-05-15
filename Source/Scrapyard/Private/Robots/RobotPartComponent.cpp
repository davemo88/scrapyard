// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartComponent.h"
#include "Parts/RobotPart.h"
#include "Parts/PartAssets.h"
#include "Materials/Material.h"
#include "Components/MeshComponent.h"

void URobotPartComponent::BeginPlay()
{
  Super::BeginPlay();
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());
}

void URobotPartComponent::SetRobotPart(URobotPart* NewRobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetRobotPart"), *GetName());
  RobotPart = NewRobotPart;
  if (GetOwner() != NULL && GetWorld() != NULL && !(GetWorld()->GetNetMode() == NM_DedicatedServer))
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::SetRobotPart - Loading Assets"), *GetName());
    SetSkeletalMesh(URobotPart::PartAssetsBP->GetAsset<USkeletalMesh>(RobotPart->SkeletalMesh));
    SetMaterial(0, URobotPart::PartAssetsBP->GetAsset<UMaterial>(RobotPart->MajorMaterial));
  }
}
