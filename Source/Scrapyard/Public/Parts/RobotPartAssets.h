// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RobotPartAssets.generated.h"

class UHeadPart;
class UCorePart;
class UArmsPart;
class ULegsPart;
class UHandheldPart;

/**
 * 
 */
UCLASS(Blueprintable)
class SCRAPYARD_API URobotPartAssets : public UObject
{
  GENERATED_BODY()

public:

  UPROPERTY(EditDefaultsOnly)
  USkeletalMesh* HeadPart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  USkeletalMesh* CorePart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  USkeletalMesh* ArmsPart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  USkeletalMesh* LegsPart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  USkeletalMesh* HandheldPart_Default_SkeletalMesh;

};
