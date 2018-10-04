// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Ability/ScrapyardAbility.h"
#include "RobotPartComponent.generated.h"

class URobotPartAssets;
class UMaterial;
class USkeletalMesh;
class UManufacturer;
class URarity;
class USoloDraft;
class URobotBodyComponent;

/**
 * 
 */
UCLASS(BlueprintType)
class SCRAPYARD_API URobotPartComponent : public USkeletalMeshComponent
{
  GENERATED_BODY()

  URobotPart* RobotPart;

public:

  virtual void BeginPlay() override;

  void SetRobotPart(URobotPart* NewRobotPart);

};
