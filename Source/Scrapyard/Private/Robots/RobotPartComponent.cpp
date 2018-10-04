// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPartComponent.h"
#include "Parts/RobotPartAssets.h"

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
  RobotPart = NewRobotPart;
}
