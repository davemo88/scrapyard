// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MenuPlayerController.h"
#include "SoloDraftPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ASoloDraftPlayerController : public AMenuPlayerController
{
  GENERATED_BODY()

  void SetupWidget() override;

  void RemoveCardWidgets();

  void AddCardWidgets();

public:
  UFUNCTION()
  void OnNextPack();
  UFUNCTION()
  void OnPartDrafted();

};
