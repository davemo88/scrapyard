// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartComponent.h"
#include "Parts/RobotPart.h"
#include "Parts/RobotPartAssets.h"
#include "Materials/Material.h"
#include "Components/MeshComponent.h"

void URobotPartComponent::BeginPlay()
{
  Super::BeginPlay();
  UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName());

//  USkeletalMesh* Mesh = GetSkeletalMesh();
//  if (Mesh != NULL)
//  {
//    SetSkeletalMesh(Mesh);
//  }
}

void URobotPartComponent::SetRobotPart(URobotPart* NewRobotPart)
{
  UE_LOG(LogTemp, Warning, TEXT("%s::SetRobotPart"), *GetName());
  RobotPart = NewRobotPart;
//  if (GetOwner() != NULL && !GetOwner()->HasAuthority())
  if (GetOwner() != NULL)
  {
    UE_LOG(LogTemp, Warning, TEXT("%s::SetRobotPart - Loading Assets"), *GetName());
    if (USkeletalMesh* Mesh = RobotPart->GetSkeletalMesh())
    {
      SetSkeletalMesh(Mesh);
    }
  
    if (UMaterial* MajorMaterial = RobotPart->GetMajorMaterial())
    {
      SetMaterial(0, MajorMaterial);
    }
  }
}
