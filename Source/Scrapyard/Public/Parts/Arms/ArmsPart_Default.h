// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parts/ArmsPart.h"
#include "ArmsPart_Default.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API UArmsPart_Default : public UArmsPart
{
  GENERATED_BODY()

public:

  UArmsPart_Default();

  virtual USkeletalMesh* GetSkeletalMesh() override;

  void BeginPlay() override { UE_LOG(LogTemp, Warning, TEXT("%s::BeginPlay"), *GetName()); GetSkeletalMesh(); };
};
