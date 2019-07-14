// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/Material.h"
#include "Engine/Texture2D.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StreamableManager.h"
#include "Animation/AnimInstance.h"
#include "UObject/NoExportTypes.h"
#include "UObject/SoftObjectPtr.h"
#include "PartAssets.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SCRAPYARD_API UPartAssets : public UObject
{
  GENERATED_BODY()

public:

  UPROPERTY(EditDefaultsOnly)
  USkeletalMesh* RobotSkeletalMesh;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<UAnimInstance> RobotAnimInstance;

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HeadPart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> CorePart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> ArmsPart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> LegsPart_Default_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HandheldPart_Default_SkeletalMesh;

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> DefaultMaterial;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> RedMaterial;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> BlueMaterial;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> GreenMaterial;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> PurpleMaterial;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UMaterial> OrangeMaterial;

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> RedCard;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> BlueCard;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> GreenCard;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> PurpleCard;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> OrangeCard;

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> HeadCardIcon;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> CoreCardIcon;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> ArmsCardIcon;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> LegsCardIcon;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> HandheldCardIcon;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<UTexture2D> ChipCardIcon;

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HeadPart_Red_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> CorePart_Red_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> ArmsPart_Red_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> LegsPart_Red_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HandheldPart_Red_SkeletalMesh;

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HeadPart_Blue_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> CorePart_Blue_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> ArmsPart_Blue_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> LegsPart_Blue_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HandheldPart_Blue_SkeletalMesh;

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HeadPart_Green_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> CorePart_Green_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> ArmsPart_Green_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> LegsPart_Green_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HandheldPart_Green_SkeletalMesh;

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HeadPart_Orange_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> CorePart_Orange_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> ArmsPart_Orange_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> LegsPart_Orange_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HandheldPart_Orange_SkeletalMesh;

  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HeadPart_Purple_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> CorePart_Purple_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> ArmsPart_Purple_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> LegsPart_Purple_SkeletalMesh;
  UPROPERTY(EditDefaultsOnly)
  TSoftObjectPtr<USkeletalMesh> HandheldPart_Purple_SkeletalMesh;
};

