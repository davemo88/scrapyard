// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Components/SkeletalMeshComponent.h"
#include "Abilities/ScrapyardAbility.h"
#include "RobotPartComponent.generated.h"

class UPartAssets;
class UMaterial;
class USkeletalMesh;
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

public:

  virtual void BeginPlay() override;

  UFUNCTION()
  void SetRobotPart(URobotPart* NewRobotPart);

protected:

  UPROPERTY(EditAnywhere)
  URobotPart* RobotPart;

};
