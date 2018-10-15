// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MenuPlayerController.h"
#include "SoloDraftPlayerController.generated.h"

class USoloDraftWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPartDraftedDelegate, URobotPart*, DraftedPart);
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
  void OnNextPack();

  FPartDraftedDelegate PartDraftedDelegate;

protected:

  UPROPERTY()
  USoloDraftWidget* SoloDraftWidget;

  void SetupWidget() override;

  UFUNCTION()
  void OnPartCardHovered(URobotPart* RobotPart);

  UFUNCTION()
  void OnPartDoubleClicked(URobotPart* RobotPart);

};
