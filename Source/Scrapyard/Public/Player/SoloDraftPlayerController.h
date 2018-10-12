// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MenuPlayerController.h"
#include "SoloDraftPlayerController.generated.h"

class USoloDraftWidget;

/**
 * 
 */
UCLASS()
class SCRAPYARD_API ASoloDraftPlayerController : public AMenuPlayerController
{
  GENERATED_BODY()

public:

  ASoloDraftPlayerController();

  UFUNCTION()
  void OnNextPack(TArray<URobotPart*> NextPack);

protected:

  UPROPERTY()
  USoloDraftWidget* SoloDraftWidget;

  void SetupWidget() override;

  void RemoveCardWidgets();

  void AddCardWidgets(TArray<URobotPart*> Parts);

  UFUNCTION()
  void OnPartCardHovered(URobotPart* RobotPart);

  UFUNCTION()
  void OnPartDrafted(URobotPart* RobotPart);
};
